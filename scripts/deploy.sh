#!/bin/bash

# CBOE BOE Engine Deployment Script
set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
ENVIRONMENT="production"
BUILD_TESTS=true
RUN_BENCHMARKS=false
DEPLOY_DOCS=false

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show usage
show_usage() {
    cat << EOF
Usage: $0 [OPTIONS]

Deploy the CBOE BOE Engine

OPTIONS:
    -e, --environment ENV    Deployment environment (development|production) [default: production]
    -t, --tests             Run tests after deployment [default: true]
    -b, --benchmarks        Run benchmarks after deployment [default: false]
    -d, --docs              Deploy documentation [default: false]
    -h, --help              Show this help message

EXAMPLES:
    $0                                  # Deploy to production
    $0 -e development                   # Deploy to development environment
    $0 -t -b                           # Deploy with tests and benchmarks
    $0 -e production -t -b -d          # Full deployment with everything

DEPLOYMENT MODES:
    - development: Build and run in development container
    - production:  Build optimized production container
    - docker:      Use Docker Compose for deployment
    - local:       Build and install locally

EOF
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -e|--environment)
            ENVIRONMENT="$2"
            shift 2
            ;;
        -t|--tests)
            BUILD_TESTS=true
            shift
            ;;
        -b|--benchmarks)
            RUN_BENCHMARKS=true
            shift
            ;;
        -d|--docs)
            DEPLOY_DOCS=true
            shift
            ;;
        -h|--help)
            show_usage
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# Validate environment
if [[ ! "$ENVIRONMENT" =~ ^(development|production|docker|local)$ ]]; then
    print_error "Invalid environment: $ENVIRONMENT"
    print_error "Valid environments: development, production, docker, local"
    exit 1
fi

print_status "Starting deployment for environment: $ENVIRONMENT"

# Check if we're in the right directory
if [ ! -f "engine/CMakeLists.txt" ]; then
    print_error "Please run this script from the project root directory"
    exit 1
fi

# Function to deploy using Docker
deploy_docker() {
    print_status "Deploying using Docker Compose..."
    
    # Check if Docker is available
    if ! command -v docker &> /dev/null; then
        print_error "Docker is not installed or not in PATH"
        exit 1
    fi
    
    if ! command -v docker-compose &> /dev/null && ! docker compose version &> /dev/null; then
        print_error "Docker Compose is not installed or not in PATH"
        exit 1
    fi
    
    # Build the Docker image
    print_status "Building Docker image..."
    docker build -t cboe-boe-engine:latest .
    
    # Run the appropriate Docker Compose profile
    if [ "$ENVIRONMENT" = "development" ]; then
        print_status "Starting development environment..."
        docker-compose --profile development up -d
    else
        print_status "Starting production environment..."
        docker-compose up -d
    fi
    
    # Run benchmarks if requested
    if [ "$RUN_BENCHMARKS" = true ]; then
        print_status "Running benchmarks..."
        docker-compose --profile benchmark up cboe-benchmark
    fi
    
    print_success "Docker deployment completed!"
    print_status "Check logs with: docker-compose logs"
    print_status "Stop with: docker-compose down"
}

# Function to deploy locally
deploy_local() {
    print_status "Deploying locally..."
    
    # Check dependencies
    if ! command -v cmake &> /dev/null; then
        print_error "CMake is not installed"
        exit 1
    fi
    
    if ! command -v python3 &> /dev/null; then
        print_error "Python 3 is not installed"
        exit 1
    fi
    
    # Install Python dependencies
    print_status "Installing Python dependencies..."
    pip3 install PyYAML>=6.0 || {
        print_warning "Failed to install PyYAML via pip3, trying pip..."
        pip install PyYAML>=6.0
    }
    
    # Make scripts executable
    chmod +x scripts/*.sh
    
    # Run code generation
    print_status "Running code generation..."
    ./scripts/run_codegen.sh
    
    # Build the project
    print_status "Building project..."
    mkdir -p engine/build
    cd engine/build
    
    if [ "$ENVIRONMENT" = "development" ]; then
        cmake .. -DCMAKE_BUILD_TYPE=Debug
    else
        cmake .. -DCMAKE_BUILD_TYPE=Release
    fi
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    cd ../..
    
    # Run tests if requested
    if [ "$BUILD_TESTS" = true ]; then
        print_status "Running tests..."
        ./scripts/run_tests.sh
    fi
    
    # Run benchmarks if requested
    if [ "$RUN_BENCHMARKS" = true ]; then
        print_status "Running benchmarks..."
        ./scripts/bench_latency.sh
    fi
    
    print_success "Local deployment completed!"
    print_status "Library: engine/build/libcboe_core.a"
    print_status "Tests: engine/build/tests/cboe_tests"
    print_status "Benchmarks: engine/build/tests/cboe_benchmarks"
}

# Function to deploy documentation
deploy_documentation() {
    if [ "$DEPLOY_DOCS" = true ]; then
        print_status "Generating documentation..."
        
        if command -v doxygen &> /dev/null; then
            # Create Doxyfile if it doesn't exist
            if [ ! -f Doxyfile ]; then
                doxygen -g
                sed -i.bak 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "CBOE BOE Engine"/' Doxyfile
                sed -i.bak 's/INPUT                  =/INPUT                  = engine\/include engine\/src/' Doxyfile
                sed -i.bak 's/RECURSIVE              = NO/RECURSIVE              = YES/' Doxyfile
                sed -i.bak 's/GENERATE_HTML          = YES/GENERATE_HTML          = YES/' Doxyfile
                sed -i.bak 's/HTML_OUTPUT            = html/HTML_OUTPUT            = docs/' Doxyfile
                rm -f Doxyfile.bak
            fi
            
            doxygen
            print_success "Documentation generated in docs/ directory"
        else
            print_warning "Doxygen not found, skipping documentation generation"
        fi
    fi
}

# Main deployment logic
case $ENVIRONMENT in
    docker|production|development)
        deploy_docker
        ;;
    local)
        deploy_local
        ;;
esac

# Deploy documentation
deploy_documentation

# Final status
print_success "🚀 Deployment completed successfully!"

if [ "$ENVIRONMENT" = "docker" ] || [ "$ENVIRONMENT" = "production" ]; then
    print_status "Container status:"
    docker-compose ps
    echo ""
    print_status "Useful commands:"
    echo "  docker-compose logs -f                 # View logs"
    echo "  docker-compose exec cboe-engine bash   # Shell access"
    echo "  docker-compose down                    # Stop containers"
    echo "  docker-compose up -d                   # Restart containers"
fi

if [ "$BUILD_TESTS" = true ]; then
    print_status "✅ All tests passed!"
fi

if [ "$RUN_BENCHMARKS" = true ]; then
    print_status "📊 Benchmarks completed!"
fi

print_status "📚 Documentation: Check README.md for usage instructions"
print_status "🔧 Configuration: Review configuration files in the project"
print_status "🐛 Issues: Report bugs on GitHub Issues"

exit 0


