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



This is the **Master Operations Manual** for your Distributed Applied Math Cluster.

You have transitioned from a standard computer user to a **Systems Administrator**. This document covers every component we built, how to operate it, and how to maintain it.

**Action:** Save this text as `README.md` in the root of your `University` folder so it syncs to all your devices.

---

# 🚀 Distributed Compute Cluster: Operations Manual

## 1. System Architecture

**Philosophy:** Separation of concerns.

- **The Server (Bazzite/PC):** Heavy compute, AI inference, Compilation, File Hosting.
    
- **The Console (MacBook M4):** The interface for coding and writing. Distraction-free.
    
- **The Controller (iPhone 16):** Authentication, Ignition (WoL), and quick reference.
    

---

## 2. Daily Start-Up Sequence

### ⚡ Ignition (Wake-on-LAN)

1. **Condition:** iPhone must be on **Local Wi-Fi**.
    
2. **Action:** Open **"Wake Me Up"** app on iPhone → Tap **PC**.
    
3. **Verification:** Listen for fans spinning up.
    
4. **Troubleshooting:** If it fails, ensure the PC wasn't hard-unplugged (Windows driver settings persist only if Soft-Shutdown was used).
    

### 🔗 Connection

1. **On Mac:** Open Terminal or VS Code.
    
2. **Connect:** `ssh compute` (or use VS Code Remote-SSH extension).
    
3. **Tunneling:** Your SSH config automatically forwards ports `8080`, `3003`, `8888`, etc., to `localhost`.
    

### 🌍 Remote Access (Cafe Mode)

1. **Pre-requisite:** PC must be **ON** (Wake-on-LAN does not work over internet without a bridge).
    
2. **Network:** Enable **Tailscale** on Mac/iPhone.
    
3. **Exit Node:** (Optional) In Tailscale settings, set "Exit Node" to your PC to encrypt public Wi-Fi traffic.
    
4. **Access:** Use `http://compute:PORT` in browser.
    

---

## 3. The Workstation (Coding & Math)

**The Environment:** You work inside an Arch Linux container called `math-lab`.

### 🖥️ Access

- **Command:** `lab` (Alias for `distrobox enter math-lab`).
    
- **Location:** You start in `~/` (Home). Your files are in `~/University`.
    

### 🛠️ Development Workflows

|**Task**|**Command / Action**|
|---|---|
|**Quick Nav**|`z cs101` (Zoxide jumps to CS101 folder)|
|**C Coding**|Edit in VS Code. Run `make run` in terminal.|
|**Python/Math**|Run `jupyter lab --no-browser --port=8888`. Open `localhost:8888`.|
|**Visualization**|Run `manim -qm file.py SceneName`. Video saves to `media/`.|
|**Search History**|Press `Ctrl + R` and type a command to find it.|

### 💾 Backup Routine (Git)

Syncthing syncs files instantly, but **Git** saves history.

- **End of Session:**
    
    Bash
    
    ```
    cd ~/University
    git add .
    git commit -m "Finished homework for [Date]"
    git push
    ```
    

---

## 4. The Intelligence (AI Stack)

**The Brain:** Local Qwen 7B (Optimized) running on RTX 4080.

### 💬 Chat Interfaces

1. **The "Matrix" Mode (Fastest):**
    
    - Open Terminal (Bazzite Host).
        
    - Command: `ai`.
        
    - Usage: Pure text chat. Exit with `/bye`.
        
2. **The "Web" Mode (Rich Text):**
    
    - Open Browser.
        
    - URL: `http://compute:8080`.
        
    - Usage: Code formatting, history saving.
        

---

## 5. Mission Control (Web Services)

You have a suite of services running in Podman containers.

### 🏠 Dashboard

- **URL:** `http://compute:3003` (Heimdall).
    
- **Usage:** Your "Start Page". Click icons to launch other tools.
    

### 🛡️ Network Defense

- **URL:** `http://compute:3002` (AdGuard Home).
    
- **Usage:** Blocks ads network-wide. Configure Blocklists here.
    

### 📂 File Management

- **URL:** `http://compute:8384` (Syncthing).
    
- **Sync Logic:**
    
    - **Mac:** `~/University` ↔ **PC:** `/home/bazzite/University` ↔ **iPhone:** `Mobius Sync/University`.
        
    - **Conflict:** If files don't appear, check this dashboard on all devices to see if one is "Disconnected".
        

### 📝 Productivity Stack

- **Vikunja (Tasks):** `http://compute:3456`. Project management.
    
- **Actual Budget:** `http://compute:5006`. Finance tracking.
    
- **Glances:** `http://compute:61208`. System/Resource monitor.
    

---

## 6. Maintenance & Updates

You are the SysAdmin. Keep the engines clean.

### 🔄 Weekly Update

Run this **one command** on the Bazzite Host to update everything (OS, Lab, AI):

Bash

```
update-all
```

_(This runs `ujust update`, `distrobox upgrade`, and pulls the latest Qwen model)._

### 🧹 Cleanup

If `podman ps` shows clutter or crashed containers:

Bash

```
podman container prune
```

---

## 7. Port Reference Map

|**Service**|**Port**|**Internal IP**|**External URL**|
|---|---|---|---|
|**Heimdall**|`3003`|Host|`http://compute:3003`|
|**Open WebUI**|`8080`|Host|`http://compute:8080`|
|**AdGuard**|`3002`|Host|`http://compute:3002`|
|**Jupyter**|`8888`|Container|`http://compute:8888`|
|**Syncthing**|`8384`|Host|`http://compute:8384`|
|**Vikunja**|`3456`|Host|`http://compute:3456`|
|**Actual**|`5006`|Host|`http://compute:5006`|
|**Glances**|`61208`|Host|`http://compute:61208`|

---

## 8. Troubleshooting Guide

- **"Command not found: podman"**
    
    - _Cause:_ You are inside the `math-lab`.
        
    - _Fix:_ Type `exit` to return to Bazzite Host.
        
- **"Command not found: gcc / manim"**
    
    - _Cause:_ You are on the Bazzite Host.
        
    - _Fix:_ Type `lab` to enter the container.
        
- **"Connection Refused" (Browser)**
    
    - _Cause:_ Container is stopped or Firewall is blocking.
        
    - _Fix:_ `podman start [container_name]` OR `sudo firewall-cmd --add-port=[PORT]/tcp`.
        
- **"Wake on LAN not working"**
    
    - _Cause:_ Windows Fast Startup re-enabled itself or iPhone permission revoked.
        
    - _Fix:_ Check BIOS and Windows Control Panel power settings.
        

---

End of Manual.

Current Status: Ready for Academic Work.


You have built a complex machine with many moving parts (Bazzite, Arch Linux, Podman Containers, AI Models, Network Tunnels).

If you don't maintain it, **it will eventually break** (storage will fill up, keys will expire, or updates will conflict).

Here is your **SysAdmin Maintenance Schedule** to keep your cluster running forever.

---

### 📅 Daily Routine (The "Save Game")

_Do this every time you finish studying._

1. Backup Your Brain (Git)

Syncthing syncs files, but if you accidentally delete a 20-page thesis on your Mac, it deletes it on your PC too. Git is your only protection against mistakes.

- **Command (Inside `lab`):**
    
    Bash
    
    ```
    cd ~/University
    git add .
    git commit -m "End of day backup"
    git push
    ```
    

---

### 📅 Weekly Routine (The "Sunday Clean-Up")

_Do this once a week to keep software fresh._

1. Run the Master Update

You created an alias for this. It updates Bazzite (OS), Arch (Math Lab), and your AI models.

- **Command (Bazzite Host):**
    
    Bash
    
    ```
    update-all
    ```
    
    _(This runs `ujust update`, `distrobox upgrade`, and `ollama pull`)_.
    

2. Update Your Containers

Your update-all handles the OS, but not the containers like Vikunja, AdGuard, or Heimdall. Use Podman Auto-Update.

- **Command (Bazzite Host):**
    
    Bash
    
    ```
    podman auto-update
    ```
    
    _Note: This only works if you created containers with `--label "io.containers.autoupdate=registry"`. Since we did manual `podman run` commands, the manual way is:_
    
    Bash
    
    ```
    # Stop, Pull, and Restart specific containers (Example for AdGuard)
    podman stop adguard
    podman rm adguard
    podman pull docker.io/adguard/adguardhome:latest
    # ... Then run the long install command again.
    ```
    
    _Better Way:_ Install **Watchtower** (from the list of 50 apps) to do this automatically for you.
    

---

### 📅 Monthly Routine (The "Deep Clean")

_Do this on the 1st of every month._

1. Prune the Garbage (Disk Space)

Podman keeps old versions of containers and AI models. After a few months, this can eat 50GB+ of space.

- **Command (Bazzite Host):**
    
    Bash
    
    ```
    podman system prune -a
    ```
    
    - _Warning:_ It will ask for confirmation. Type `y`.
        
    - _What it does:_ Deletes stopped containers and unused images. It will **not** delete your data (volumes).
        

2. Check Tailscale Keys

Tailscale security keys expire every 90 days by default. If your PC suddenly "disappears" from your Mac, this is why.

- **Action:** Go to [login.tailscale.com](https://login.tailscale.com/) -> **Machines**.
    
- **Check:** Look for "Key Expiry" on your Bazzite PC.
    
- **Fix:** Click **...** -> **Disable Key Expiry** (Recommended for a stationary server).
    

3. Physical Dust Check

You have an RTX 4080. It moves a lot of air.

- **Action:** Look at the front intake filters of your PC case. If they are gray, wipe them. Heat kills performance.
    

---

### 🚑 Emergency Procedures (When Things Break)

Scenario 1: Bazzite Update Broke Something

Since Bazzite is "Immutable," you can time-travel back to yesterday.

- **Command:**
    
    Bash
    
    ```
    rpm-ostree rollback
    ```
    
- **Action:** Reboot. You are now back on the previous version of the OS.
    

Scenario 2: "Container Name Already in Use"

If you try to restart a service and it fails:

- **Command:**
    
    Bash
    
    ```
    podman rm -f [container_name]
    ```
    
    _(Then run the install command again)._
    

Scenario 3: "Disk Full"

If you downloaded too many LLMs:

- **Check usage:** `df -h`
    
- **Delete models:** `podman exec -it ollama ollama rm [model_name]`
    

---

### 📜 Summary Checklist

|**Frequency**|**Task**|**Command**|
|---|---|---|
|**Daily**|Git Push|`git push`|
|**Weekly**|Update OS/Lab|`update-all`|
|**Monthly**|Clean Disk|`podman system prune -a`|
|**Monthly**|Check Tailscale|(Web Console)|
|**Yearly**|Dust PC|(Physical)|

**You are now fully certified to run this cluster.**