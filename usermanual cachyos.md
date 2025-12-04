
This is the final **System Operations Manual** for your CachyOS Distributed Study Cluster. It consolidates every configuration we have made, from the lowest-level networking to the highest-level workflows.

---

# 📚 CachyOS Homelab Operations Manual

## 1. System Overview and Initial Access

Your setup is a **Client-Server Architecture**. All heavy lifting (AI, compiling, streaming) happens on the CachyOS PC, accessed remotely by your Mac and iPhone.

|**Component**|**Role**|**Access Method**|
|---|---|---|
|**PC (CachyOS)**|**Compute Server** (RTX 4080)|SSH / Moonlight|
|**MacBook**|**Client Console** (Input / Viewing)|`ssh compute`|
|**iPhone**|**Controller** (WoL / Access)|Tailscale App|

### 1.1 The Ignition Sequence (WoL)

This bypasses the physical power button on the PC.

- **Action:** Open the **"Wake Me Up"** app on your iPhone (must be on the local Wi-Fi).
    
- **Success:** PC powers on automatically.
    

### 1.2 SSH Terminal Access (The Key)

Your Mac's config file (`~/.ssh/config`) holds the key to the entire network.

- **Command:** Open Mac Terminal → Type `ssh compute`.
    
- **Result:** You are instantly logged into CachyOS as user `kazo`.
    

---

## 2. The Core Workstation (The Lab)

All primary development work happens inside the isolated Arch Linux environment named `math-lab`.

### 2.1 Shell & Navigation (QoL)

- **Enter Workstation:** Type `lab` (Alias for `distrobox enter math-lab`).
    
- **Go to Assignments:** Type `uni` (Alias for `cd ~/University/Semester_01`).
    
- **Terminal Features:** The **Starship** prompt, **Zoxide** (smart `cd`), and **FZF** (`Ctrl+R` for history search) are all installed and working inside the lab.
    

### 2.2 Coding and Math Workflows

|**Task**|**Command**|**Access URL**|**Notes**|
|---|---|---|---|
|**C/C++ Build**|`make run` or `gcc ... -lraylib`|Moonlight|**Must be run inside `lab`**. Use Moonlight to view graphical output.|
|**Start Jupyter**|`jupyter lab --ip=0.0.0.0 --port=8888`|`http://compute:8888`|Must be running in a live terminal session.|
|**Symbolic Math**|Use Python / SymPy kernel in Jupyter.|`http://compute:8888`|For integration and symbolic proofs.|
|**GPU Test (Manim)**|`manim -qm file.py SceneName`|File Explorer|Uses the RTX 4080 to render math videos.|

---

## 3. The Central Command Center (Web Services)

|**Service**|**Purpose**|**Port**|**Access URL (On Mac/iPhone)**|
|---|---|---|---|
|**Heimdall**|**Dashboard** / Launchpad|`3003`|`http://compute:3003`|
|**AI Tutor**|Qwen 7B Interface|`8080`|`http://compute:8080`|
|**AdGuard Home**|DNS-level Ad Blocking|`3002`|`http://compute:3002` (Admin Portal)|
|**Syncthing GUI**|File Sync Status|`8384`|`http://compute:8384`|
|**Actual Budget**|Finance Tracking|`5006`|`http://compute:5006`|

---

## 4. Data Safety and Maintenance

### 4.1 Data Synchronization

- **Method:** **Syncthing** (File-level) and **Git** (Code History).
    
- **Folder:** `~/University` is synced between CachyOS, Mac, and iPhone (via Mobius Sync).
    
- **Status Check:** Open the Syncthing GUI (`http://compute:8384`) and confirm all three devices say **"Up to Date" (Green)**.
    

### 4.2 The Backup Ritual (Git)

Syncthing syncs immediately, but Git is your official "Time Machine."

**The Daily Routine (Run inside `lab` terminal):**

Bash

```
git add .
git commit -m "End of day progress"
git push
```

### 4.3 Cluster Maintenance (The Weekly Update)

The entire system needs to be updated weekly. The alias handles all three subsystems:

**Run this on the CachyOS Host Terminal:**

Bash

```
update-all
```

- **What it does:**
    
    1. `sudo pacman -Syu` (Updates CachyOS base).
        
    2. `distrobox upgrade --all` (Updates the Arch Lab).
        
    3. `podman exec ... ollama pull` (Checks for new AI models).
        

### 4.4 Emergency & Cleanup

- **Container Crash:** If an app stops, run `podman start [container_name]` (e.g., `podman start ollama`).
    
- **System Rollback:** If an update breaks the OS, use `sudo timeshift --restore` (or if you used Btrfs, `snapper rollback`) to revert the system to a previous working state.