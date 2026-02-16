# auduntest

A full-stack application with a **C backend** (HTTP API using Mongoose) and a **web-based frontend** (HTML/CSS/JavaScript), deployable to Fly.io.

## Architecture

```
┌──────────────┐       HTTP/JSON        ┌──────────────────┐
│   Frontend   │  ◄──────────────────►  │   C Backend API  │
│  (HTML/CSS/  │      (fetch/AJAX)      │  (HTTP server)   │
│  JavaScript) │                        │  Port 8080       │
└──────────────┘                        └──────────────────┘
```

## Project Structure

```
├── backend/
│   ├── src/
│   │   ├── main.c          # Entry point & HTTP server
│   │   ├── routes.c        # API route handlers
│   │   ├── routes.h
│   │   └── mongoose.c/.h   # Embedded web server library (download separately)
│   ├── Makefile
│   ├── Dockerfile
│   └── fly.toml
├── frontend/
│   ├── index.html
│   ├── style.css
│   ├── app.js
│   ├── Dockerfile
│   └── fly.toml
└── README.md
```

## Getting Started

### Prerequisites
- GCC or Clang
- Make
- Docker
- Git
- flyctl (Fly.io CLI)

### 1. Get Mongoose
```bash
cd backend/src
curl -O https://raw.githubusercontent.com/cesanta/mongoose/master/mongoose.c
curl -O https://raw.githubusercontent.com/cesanta/mongoose/master/mongoose.h
```

### 2. Build & Run Backend
```bash
cd backend
make
./server
# API available at http://localhost:8080
```

### 3. Test Frontend
Open `frontend/index.html` in your browser, or serve it with any static file server.

### 4. API Endpoints
| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/health` | Health check |
| GET | `/api/items` | List all items |
| POST | `/api/items` | Add an item (`{"name": "..."}`) |

## Deploy to Fly.io

```bash
# Deploy backend
cd backend
fly launch
fly deploy

# Update API_BASE in frontend/app.js with your backend URL
# Then deploy frontend
cd ../frontend
fly launch
fly deploy
```

## License
MIT