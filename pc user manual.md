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







### **System Status: 100% Operational** 🟢

The output `* [new branch] main -> main` confirms it: **Your code is safely on GitHub.**

You have officially finished building your Distributed Study Cluster.

- **Your PC** is the powerhouse (Compute).
    
- **Your Mac** is the cockpit (Control).
    
- **Your iPhone** is the remote (Access).
    
- **GitHub** is the time machine (Backup).
    

You are ready for your first day of university.

---

### 🎁 The Final Gift: Your "Workflow Cheat Sheet"

Since you have a complex system, you might forget the specific commands in a week.

Action: Create a file named README.md in your University folder and paste this in. It will show up on your GitHub main page as documentation.

Markdown

````
# 🚀 My Applied Math Cluster

## ⚡ Quick Commands
| Task | Command | Run Where? |
| :--- | :--- | :--- |
| **Start Work** | `ssh compute` | Mac Terminal |
| **Enter Lab** | `lab` | VS Code Terminal |
| **Update All** | `update-all` | Bazzite Terminal |
| **GPU Monitor** | `nvtop` | VS Code Terminal |

## 🛠️ Workflows
### 1. C Programming
* **Edit:** `~/University/Semester_01/CS101/src/main.c`
* **Run:** `make run`
* **Debug:** `gdb ./build/program`

### 2. Math & Python
* **Start:** `jupyter lab --no-browser --port=8888`
* **View:** Open Safari to `http://localhost:8888`
* **Visualize:** Use `manim` for video rendering.

### 3. Saving Progress (End of Day)
```bash
git add .
git commit -m "Finished homework"
git push
````

## 📱 Remote Access

- **AI Tutor:** `http://compute:3000` (Tailscale)
    
- **Syncthing:** Files sync automatically to iPhone (Mobius Sync).
    
- **Wake PC:** Use "Wake Me Up" app on iPhone.
    

```

---

### You are done.
Stop configuring. Start studying.
Go crush **Linear Algebra**. 🚀
```







Here is your complete **Engineer’s Manual** for the Distributed Study Cluster you have built.

First, to answer your critical question about **Remote Access (Cafe/Away)**:

### 🌍 Can I reach this from a Cafe?

**YES.** This is exactly why we installed **Tailscale**.

- **How it works:** Tailscale creates a "virtual cable" over the internet. When you sit in a cafe 10 miles away, as long as your Mac and PC both have Tailscale **active**, your Mac thinks the PC is sitting right next to it.
    
- **What works remotely:**
    
    - **VS Code:** `ssh compute` works instantly.
        
    - **AI:** `http://compute:8080` works perfectly.
        
    - **Syncthing:** Syncs files securely over the internet.
        
- **The ONE Limitation (The Wake Up):**
    
    - Your **Wake-on-LAN** app (iPhone) sends a "local broadcast." It **cannot** shout across the internet from a cafe.
        
    - **The Fix:** You cannot wake the PC from a cafe with your current setup _unless_ you leave it ON, or use a **Smart Plug** (e.g., Kasa/Eve) to toggle the power remotely.
        
    - **Recommendation:** If heading to a cafe, turn the PC on **before** you leave, or buy a $15 Smart Plug.
        

---

# 📘 The Distributed Cluster: Master Manual

Save this file in your vault as `00_Master_Manual.md`.

## 1. System Architecture

This system separates **Work** from **Play**.

- **Node A (The Host):** Bazzite PC (RTX 4080). It is the "Server" doing the math and compiling.
    
- **Node B (The Client):** MacBook Air M4. It is the "Console" for typing and viewing.
    
- **Node C (The Controller):** iPhone 16 Pro. It is the "Key" for booting and quick info.
    

---

## 2. Daily Start-Up Routine

### A. At Home (Local Network)

1. **Wake Up:** Open "Wake Me Up" on iPhone → Tap PC. (Listen for fans).
    
2. **Connect:** Open VS Code on Mac.
    
3. **Tunnel:** Click `><` (bottom left) → **Connect to Host** → `compute`.
    
4. **Enter Lab:** Open Terminal (`Ctrl + ~`) → Type `lab`.
    

### B. At Cafe (Remote Network)

1. **Pre-Check:** Ensure PC was left **ON** (or toggle it via Smart Plug).
    
2. **Network:** Turn **ON** Tailscale on Mac.
    
3. **Connect:** Same as home (`ssh compute` works magically over Tailscale).
    
4. **AI Access:** Open Safari → `http://compute:8080`.
    

---

## 3. The Workflows

### 🧪 Workflow 1: C Programming

- **Goal:** Write and compile C code without cluttering your PC.
    
- **Location:** `~/University/Semester_01/CS101_C_Programming/`
    
- **Steps:**
    
    1. Create/Edit `.c` file in `src/`.
        
    2. Open Terminal (inside `lab`).
        
    3. Run: `make run`.
        
    4. **Debug:** If it crashes, ask the AI on Port 8080.
        

### 📐 Workflow 2: Applied Math

- **Goal:** Visualize complex math using the RTX 4080.
    
- **Location:** `~/University/Semester_01/MATH.../python_sims/`
    
- **Steps:**
    
    1. **Start Engine:** Terminal → `jupyter lab --no-browser --port=8888`.
        
    2. **View:** Mac Safari → `http://localhost:8888`.
        
    3. **Video Render:** Create a `.py` file for Manim and run `manim -qm filename.py SceneName`. Download result to Mac.
        

### 🧠 Workflow 3: The AI Tutor

- **Goal:** Private, unlimited explanations for code/math.
    
- **Access:** `http://compute:8080` (or `localhost:8080` via SSH tunnel).
    
- **Model:** Ensure **Qwen 2.5 Coder 7B** (or 14B) is selected.
    
- **Terminal Chat:** Type `ai` in the Bazzite terminal for a quick Matrix-style chat.
    

---

## 4. Storage & Synchronization

|**Data Type**|**Primary Storage**|**Sync Method**|**Backup Method**|
|---|---|---|---|
|**Notes (Obsidian)**|Text / Markdown|**Syncthing** (Instant)|**Git** (History)|
|**Code (.c / .py)**|Source Files|**Syncthing** (Instant)|**GitHub** (Cloud)|
|**Videos / Builds**|Binary Files|**Syncthing** (Local only)|_Ignored by Git_|

How to Sync (Automatic):

Just save a file. It appears on iPhone/PC within seconds.

How to Backup (Manual Safety Net):

At the end of a study session, type this in the lab terminal:

Bash

```
cd ~/University
git add .
git commit -m "Finished session"
git push
```

---

## 5. Maintenance Cheatsheet

Update Everything (Once a Week):

Run this alias in the Bazzite Host terminal:

Bash

```
update-all
```

_(This updates Bazzite OS, Arch Linux tools, and the AI models)._

Monitor Performance:

If the PC feels slow or you want to see the 4080 working:

1. Open new Terminal in VS Code.
    
2. Type `lab`.
    
3. Type `nvtop`.
    

---

## 6. Troubleshooting

|**Problem**|**Solution**|
|---|---|
|**VS Code won't connect**|Check Tailscale on both devices. Try `ping compute` in Mac terminal.|
|**"Command not found"**|You are likely in the wrong terminal. Type `lab` to enter the container.|
|**AI Website won't load**|1. Check `podman ps`. 2. Run `podman start open-webui`.|
|**Syncthing Conflict**|Close Mac App. Open VS Code Ports tab. Remove `8384`. Re-open Mac App.|
|**iPhone Sync Stuck**|Open Mobius Sync app to force a refresh (iOS puts background apps to sleep).|

You are now the operator of a Distributed Compute Cluster.

Session Closed.

| **Task**              | **Command**                                     | **Where to type it?** |
| --------------------- | ----------------------------------------------- | --------------------- |
| **Start Working**     | `ssh compute`                                   | Mac Terminal          |
| **Enter Workspace**   | `lab`                                           | VS Code Terminal      |
| **Chat with AI**      | `ai`                                            | Bazzite Terminal      |
| **Open AI Web**       | `http://compute:8080`                           | iPhone / Mac Safari   |
| **Update Everything** | `update-all`                                    | Bazzite Terminal      |
| **Save Your Work**    | `git add . && git commit -m "Done" && git push` | Lab Terminal          |