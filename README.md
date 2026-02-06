
# Terminal Multiplayer Tic-Tac-Toe  
Operating Systems Project (Roll No. 41–50)

A process-based multiplayer Tic-Tac-Toe game built in C using Linux IPC mechanisms. The game runs across separate terminals, supports multiple concurrent matches, and demonstrates core OS concepts like inter-process communication, synchronization, and resource management.

---

## Project Objective

To design a multiplayer game system that showcases key Operating System concepts including:

- Inter-Process Communication (IPC)
- Process synchronization
- Named Pipes (FIFOs)
- Dynamic resource allocation
- Concurrent process handling

---

## Features

| Feature | Description |
|--------|-------------|
| PID-based Game Rooms | Each host creates a unique game session using its process ID |
| Password Protection | Joiner must authenticate before the game starts |
| Multiplayer | Two players play from separate terminals |
| Spectator Mode | Third process can watch the game live |
| Smart Game Logic | Win detection and draw detection |
| Invalid Move Handling | Immediate retry without switching turns |
| Replay Option | Play multiple rounds in one session |
| Scoreboard | Results stored with timestamps in a file |
| Multiple Games | Several matches can run simultaneously |

---

## Technologies Used

- Language: C  
- Platform: Linux / UNIX Terminal  
- OS Concepts: IPC, FIFOs, Process Control  

---

## Project Files

| File | Purpose |
|------|--------|
| `host.c` | Game host (Player X) |
| `join.c` | Game joiner (Player O) |
| `spec.c` | Spectator viewer |
| `scoreboard.txt` | Stores match results |

---

## Compilation

```bash
gcc host.c -o host
gcc join.c -o join
gcc spec.c -o spec
