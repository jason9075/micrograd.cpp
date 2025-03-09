.DEFAULT_GOAL:=help

.PHONY: run
run: build					## Run the application
	echo "Running the application..."
	./playground.app

.PHONY: build
build:						## Build the application
	echo "Building the application..."
	mkdir -p build
	@(cd build && cmake .. && make)

.PHONY: test
test:						## Run tests
	echo "Running tests..."
	./tests.app


.PHONY: clean
clean:						## Clean the docker images
	@rm -rf build
	@rm -f playground.app tests.app

.PHONY: help
help:						## Show this help
	echo "Makefile for local development"
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m<target>\033[0m (default: help)\n\nTargets:\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-18s\033[0m %s\n", $$1, $$2 }' $(MAKEFILE_LIST)
