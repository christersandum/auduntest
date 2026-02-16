# ---- Build stage ----
FROM gcc:latest AS builder
WORKDIR /app
COPY src/ src/
COPY Makefile .
RUN make

# ---- Run stage ----
FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY --from=builder /app/server .
EXPOSE 8080
CMD ["./server"]