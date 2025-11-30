Yes. **Any file** you drag and drop into the `~/University` folder on your Mac (using Finder) will instantly be encrypted, chopped into blocks, and beamed over to your Bazzite PC.

You can dump PDF textbooks, old markdown notes, or images there. They will appear on your iPhone and PC automatically.

---

### Your System Manual

Here is the master documentation for the system you just engineered.

**Action:** Create a new note in Obsidian called `00_System_Manual.md` and paste this entire block inside.

Markdown

````
# 🛠️ Distributed Study Cluster: User Manual

## 1. System Architecture
- **Compute Node (Host):** Bazzite PC (RTX 4080). Handles compilation, AI inference, and rendering.
- **Console (Client):** MacBook Air M4. Handles typing, viewing, and battery life.
- **Controller:** iPhone 16 Pro. Handles authentication and Wake-on-LAN.
- **Engine:** Arch Linux Container (`math-lab`) inside Bazzite.

---

## 2. Daily Startup Routine
1.  **Wake Up:** Use "Wake Me Up" app or Smart Plug on iPhone to turn on PC.
2.  **Connect:** Open VS Code on Mac → Click `><` (bottom left) → **Connect to Host** → `compute`.
3.  **Enter Lab:** Open VS Code Terminal (`Ctrl + ~`) and type:
    ```bash
    distrobox enter math-lab
    ```
    *(Verify prompt says `[bazzite@math-lab]`)*.

---

## 3. Workflow: C Programming
**Location:** `~/University/Semester_01/CS101_C_Programming/`

1.  **Write Code:** Edit files in `src/`.
2.  **Compile & Run:** In the terminal:
    ```bash
    make run
    ```
    *(This automatically compiles `src/*.c` and runs the binary in `build/`).*

---

## 4. Workflow: Applied Math (Python/Jupyter)
**Location:** `~/University/Semester_01/MATH102.../python_sims/`

1.  **Start Engine:** In VS Code terminal (inside math-lab):
    ```bash
    jupyter lab --no-browser --port=8888
    ```
2.  **View Interface:** Open Safari on Mac → `http://localhost:8888`.
3.  **Usage:** Use this for Linear Algebra visualizations, plotting, and calculus checks.

---

## 5. Workflow: AI Tutor (Qwen 3 Coder)
**Status:** Running quietly in the background on the PC.

1.  **Access:** Open Safari on Mac/iPhone → `http://localhost:3000`.
2.  **Model:** Ensure **Qwen 2.5/3 Coder** is selected.
3.  **Rule:** Use this for explaining pointers, debugging code, and summarizing math theorems. Do not use for writing your essays.

---

## 6. Syncing Notes (Obsidian)
**Status:** Automatic via Syncthing.

* **Mac:** Files live in `~/University`.
* **PC:** Files live in `/home/bazzite/University`.
* **Conflict?** If Sync fails, open `http://localhost:8384` (Mac) and `localhost:54321` (PC Tunnel via VS Code Ports) to check status.

---

## 7. System Maintenance (Once a Week)
Run these inside the **Bazzite Terminal** (NOT inside math-lab):

```bash
# 1. Update the Host OS
ujust update

# 2. Update the Arch Linux Container
distrobox upgrade --all

# 3. Update AI Brain
podman exec -it ollama ollama pull qwen2.5-coder:14b
````

## 8. Troubleshooting

- **VS Code won't connect:** Open Terminal on Mac -> `ssh compute`. If that fails, check Tailscale on iPhone to see if PC is online.
    
- **"Undefined reference to main":** You forgot to save your `.c` file before running `make`.
    
- **Syncthing GUI won't open on Mac:** Run `pkill -f syncthing` in Mac terminal, then open the App again.
    

```

### Final Words
You have built a system that separates **Leisure** (Gaming on PC) from **Work** (Computing on PC via Mac).

* **When you sit at the PC:** You Game.
* **When you sit at the Mac:** You Study.

Good luck with Semester 1. **Go calculate that Dot Product.**
```