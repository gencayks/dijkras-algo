
This is the definitive **System Operations Manual** for your distributed homelab. It consolidates every component, configuration, and workflow we have built into a single reference document.

**Action:** Save this content as `README.md` in your `~/University` folder so it syncs to all your devices.

---

# 📘 Distributed Applied Math Cluster: User Manual

Version: 1.0 (Stable)

Operator: @gencayks

## 1. System Architecture

Your setup follows a **Client-Server-Controller** model designed to separate _compute_ from _interface_.

|**Device**|**Role**|**OS**|**Hostname**|**IP (Tailscale)**|
|---|---|---|---|---|
|**PC (RTX 4080)**|**Compute Node**|Bazzite (Fedora Atomic)|`compute`|`100.x.y.z`|
|**MacBook Air M4**|**Console**|macOS|`macbook`|`100.x.x.x`|
|**iPhone 16 Pro**|**Controller**|iOS 18|`iphone`|`100.x.x.x`|

### The "Two Rooms" Concept

You must understand where you are typing commands to avoid errors.

- **The Host (Bazzite):** Managing containers, updates, and the OS.
    
    - _Prompt:_ `bazzite@DESKTOP-4K...`
        
- **The Lab (Arch Linux):** Coding, compiling, running Python/Manim.
    
    - _Prompt:_ `⬢ [math-lab] ❯`
        

---

## 2. Daily Start-Up Sequence

### ⚡ Ignition (Wake-on-LAN)

- **Goal:** Turn on the PC from your bed or couch.
    
- **Prerequisite:** iPhone must be on **Local Wi-Fi** (WoL does not cross the internet).
    
- **Action:** Open **"Wake Me Up"** app on iPhone → Tap **PC**.
    
- **Verification:** Fans spin up. If it fails, ensure you didn't force-power-off the PC (Windows drivers need a soft shutdown to keep the NIC alive).
    

### 🔗 Connection & Access

1. **Dashboard:** Open `http://compute:3003` (Heimdall) on Mac/iPhone.
    
    - _Status Check:_ Green dots on services.
        
2. **Terminal Access:** Open Terminal/VS Code on Mac.
    
    - _Command:_ `ssh compute`
        
3. **Workstation Entry:**
    
    - _Command:_ `lab` (Entering the Arch container).
        

---

## 3. The Workflows (How to actually work)

### 🧪 C & C++ Development

- **Location:** `~/University/Semester_01/CS101/src`
    
- **Edit:** VS Code (Mac) via Remote-SSH.
    
- **Compile:** Inside `lab` terminal.
    
    Bash
    
    ```
    make run
    # OR manual:
    gcc main.c -o app && ./app
    ```
    
- **Debug:** `gdb ./app` inside `lab`.
    

### 📐 Applied Math & Visualization

- **Location:** `~/University/Semester_01/MATH102/`
    
- **Python/Jupyter:**
    
    1. Terminal (in `lab`): `jupyter lab --no-browser --port=8888`
        
    2. Browser (Mac): `http://compute:8888` (Password: `math` or your token).
        
- **Manim (Video Rendering):**
    
    1. Create `scene.py`.
        
    2. Terminal (in `lab`): `manim -qm scene.py SceneName`
        
    3. View: Download `.mp4` from VS Code sidebar or view via synced folder on Mac.
        

### 🤖 AI Tutor (Qwen 7B)

- **Web Chat:** `http://compute:8080` (Open WebUI).
    
    - _Best for:_ Saving chat history, formatting code blocks.
        
- **Terminal Chat:** Type `ai` in Bazzite terminal.
    
    - _Best for:_ Quick questions while coding.
        

### 🎮 Gaming (RTX 4080 Streaming)

- **Host:** **Sunshine** running on PC.
    
- **Client:** **Moonlight** app on Mac/iPhone.
    
- **Action:** Open Moonlight → Click Desktop → Play Cyberpunk/Elden Ring at 120Hz remotely.
    
- **Emergency Quit:** `Ctrl + Option + Shift + Q` (on Mac).
    

---

## 4. Service & Port Reference

|**Service**|**Port**|**URL**|**Status**|
|---|---|---|---|
|**Heimdall** (Dashboard)|`3003`|`http://compute:3003`|✅ Active|
|**AdGuard Home** (DNS)|`3002`|`http://compute:3002`|✅ Active|
|**Open WebUI** (AI)|`8080`|`http://compute:8080`|✅ Active|
|**PDF Tools**|`8082`|`http://compute:8082`|✅ Active|
|**Syncthing** (Sync)|`8384`|`http://compute:8384`|✅ Active|
|**Vikunja** (Tasks)|`3456`|`http://compute:3456`|✅ Active|
|**Actual** (Budget)|`5006`|`http://compute:5006`|✅ Active|
|**Glances** (Monitor)|`61208`|`http://compute:61208`|✅ Active|
|**Jupyter**|`8888`|`http://compute:8888`|⚠️ **Manual Start**|

---

## 5. Storage & Backups

### 🔄 Synchronization (Live)

- **Tool:** Syncthing.
    
- **Path:** `~/University` is mirrored instantly across Mac, PC, and iPhone (Mobius).
    
- **Conflict Resolution:** If a file conflicts, Syncthing creates a `sync-conflict` copy. Check the Web UI (`:8384`) if files don't appear.
    

### 💾 Backup (Snapshots)

- **Tool:** Git + GitHub (Private Repo).
    
- **Manual Save:**
    
    Bash
    
    ```
    # Inside 'lab'
    cd ~/University
    git add .
    git commit -m "Finished homework"
    git push
    ```
    

### 🤖 Automatic Backup (The "Level 100" Upgrade)

_You asked for automation. Here is how to make Bazzite auto-push your code every hour._

1. **Create Service File:** `nano ~/.config/systemd/user/autopush.service`
    
    Ini, TOML
    
    ```
    [Unit]
    Description=Auto-Push University Git
    
    [Service]
    Type=oneshot
    WorkingDirectory=%h/University
    ExecStart=/usr/bin/podman exec math-lab git add .
    ExecStart=/usr/bin/podman exec math-lab git commit -m "Auto-save: %d"
    ExecStart=/usr/bin/podman exec math-lab git push
    ```
    
2. **Create Timer:** `nano ~/.config/systemd/user/autopush.timer`
    
    Ini, TOML
    
    ```
    [Unit]
    Description=Run Auto-Push hourly
    
    [Timer]
    OnBootSec=15min
    OnUnitActiveSec=1h
    
    [Install]
    WantedBy=timers.target
    ```
    
3. **Enable:** `systemctl --user enable --now autopush.timer`
    

---

## 6. Maintenance Procedures

### 🧹 Weekly Maintenance

Run this **Alias** on the Bazzite Host every Sunday:

Bash

```
update-all
```

- **What it does:**
    
    1. Updates Bazzite OS (`ujust update`).
        
    2. Updates Arch Linux Container (`distrobox upgrade`).
        
    3. Updates AI Models (`ollama pull`).
        

### 🚑 Troubleshooting Guide

**Problem: "Command not found: podman"**

- **Cause:** You are inside the `math-lab`.
    
- **Fix:** Type `exit` to return to Bazzite Host.
    

**Problem: "Connection Refused" on Browser**

- **Cause:** Service crashed or Firewall blocked it.
    
- **Fix 1 (Restart):** `podman start [container_name]`
    
- **Fix 2 (Firewall):** `sudo firewall-cmd --add-port=[PORT]/tcp --permanent && sudo firewall-cmd --reload`
    

**Problem: "Wake on LAN not working"**

- **Cause:** Windows Fast Startup likely re-enabled itself after an update.
    
- **Fix:** Boot Windows → Control Panel → Power Options → Uncheck "Fast Startup".
    

---

End of Manual.

System Status: Ready for Semester 1.

Access Sunshine Anywhere! (Port Forwarding/Firewall Tutorial)

This video is relevant because it details the firewall and port forwarding steps for Sunshine, ensuring your remote gaming stream works if you ever decide to access it from outside your home network.