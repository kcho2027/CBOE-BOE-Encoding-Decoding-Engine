# Multi-stage build for CBOE BOE Engine
FROM ubuntu:22.04 as builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    libgtest-dev \
    libbenchmark-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies
RUN pip3 install PyYAML>=6.0

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Make scripts executable
RUN chmod +x scripts/*.sh

# Run code generation
RUN ./scripts/run_codegen.sh

# Build the project
RUN mkdir -p engine/build && \
    cd engine/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja && \
    ninja

# Run tests to ensure everything works
RUN cd engine/build && ctest --output-on-failure

# Production stage
FROM ubuntu:22.04 as production

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Create app user
RUN useradd -m -s /bin/bash appuser

# Set working directory
WORKDIR /app

# Copy built artifacts
COPY --from=builder /app/engine/build/libcboe_core.a ./lib/
COPY --from=builder /app/engine/build/tests/cboe_tests ./bin/
COPY --from=builder /app/engine/build/tests/cboe_benchmarks ./bin/
COPY --from=builder /app/engine/include ./include/
COPY --from=builder /app/codegen ./codegen/
COPY --from=builder /app/scripts ./scripts/
COPY --from=builder /app/README.md ./

# Change ownership
RUN chown -R appuser:appuser /app

# Switch to app user
USER appuser

# Set environment variables
ENV CBOE_HOME=/app
ENV PATH="$PATH:/app/bin"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD /app/bin/cboe_tests --gtest_list_tests > /dev/null || exit 1

# Default command
CMD ["/app/bin/cboe_tests"]

# Labels
LABEL org.opencontainers.image.title="CBOE BOE Engine"
LABEL org.opencontainers.image.description="High-performance encoding/decoding engine for CBOE Binary Order Entry protocol"
LABEL org.opencontainers.image.version="1.0.0"
LABEL org.opencontainers.image.authors="CBOE BOE Engine Team"
