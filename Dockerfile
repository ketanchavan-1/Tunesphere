FROM ubuntu:24.04 AS build

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        cmake \
        g++ \
        git \
        ninja-build \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY backend ./backend
COPY frontend ./frontend
COPY database ./database
COPY README.md .

WORKDIR /app/backend
RUN cmake -S . -B build -G Ninja \
    && cmake --build build

FROM ubuntu:24.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends zlib1g \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app/backend
COPY --from=build /app/backend/build/TuneSphere ./build/TuneSphere
COPY --from=build /app/backend/storage ./storage
COPY --from=build /app/backend/music ./music
COPY --from=build /app/frontend ../frontend

EXPOSE 8080
CMD ["./build/TuneSphere"]
