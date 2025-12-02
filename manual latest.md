This is the **Master System Documentation** for your **Applied Mathematics & Engineering Homelab**.

You have successfully transitioned from a standard user to a **Systems Administrator**. This manual documents the architecture, access protocols, and operational workflows for your Distributed Compute Cluster.

---

# 📘 The Cluster: Master Operations Manual

## **1. System Architecture**

Your setup utilizes a **Distributed Compute** model. You separate the "Interface" from the "Execution."

- **Node A (The Host):** **Bazzite PC** (RTX 4080).
    
    - _Role:_ Heavy compute, AI inference, Compilation, File Hosting, Gaming Server.
        
    - _OS:_ Fedora Atomic (Immutable) + Arch Linux Container.
        
- **Node B (The Console):** **MacBook Air M4**.
    
    - _Role:_ The interface. You type here, but the code runs on Node A.
        
- **Node C (The Controller):** **iPhone 16 Pro**.
    
    - _Role:_ Authentication, Remote Ignition (WoL), Quick Access.
        

---

## **2. Network & Access Layer**

### **The Network Mesh (Tailscale)**

All devices are connected via a private, encrypted Mesh VPN.

- **Hostname:** `compute` (or IP `100.x.y.z`)
    
- **Feature:** **Exit Node** is enabled. When at a cafe, toggle "Exit Node" on Mac/iPhone to route traffic through your home PC for encryption.
    

### **Ignition Sequence (Wake-on-LAN)**

- **Tool:** "Wake Me Up" App (iPhone).
    
- **Protocol:** Sends a "Magic Packet" to MAC Address `e8:9c:25:6a:63:b3`.
    
- **Constraint:** Works only on Local Wi-Fi. (Use a Smart Plug for WAN access).
    

### **Terminal Access**

- **Command:** `ssh compute`
    
- **User:** `bazzite`
    
- **Config:** `~/.ssh/config` on Mac handles port forwarding automatically.
    

---

## **3. The Service Stack (Container Inventory)**

These are the always-on services running on your Bazzite Host.

|**Service**|**Port**|**Internal URL**|**Purpose**|
|---|---|---|---|
|**Heimdall**|`3003`|`http://compute:3003`|**Mission Control.** Your browser start page.|
|**Open WebUI**|`8080`|`http://compute:8080`|**AI Interface.** ChatGPT-like UI for Qwen.|
|**n8n**|`5678`|`http://compute:5678`|**Automation.** Workflow builder (AI Agents).|
|**AdGuard Home**|`3002`|`http://compute:3002`|**Defense.** Network-wide ad/tracker blocker.|
|**Syncthing**|`8384`|`http://compute:8384`|**Storage.** Syncs `~/University` folder.|
|**Watchtower**|`N/A`|_Background_|**Maintenance.** Auto-updates containers.|
|**Ollama**|`11434`|`localhost:11434`|**The Brain.** Hosts the Qwen model.|

---

## **4. The Workstation (Math Lab)**

This is your persistent development environment inside **Distrobox**. It isolates your tools from the Bazzite OS.

- **OS:** Arch Linux.
    
- **Access Command:** `lab` (Alias for `distrobox enter math-lab`).
    
- **Location:** `/home/bazzite/University`.
    

### **Installed Toolchain**

- **Languages:** `gcc` (C), `python` (NumPy/SciPy), `node` (JS).
    
- **Visualization:** `manim` (Math Video Render), `jupyter` (Notebooks), `raylib` (Game Dev).
    
- **CLI Enhancements:** `starship` (Prompt), `zoxide` (Navigation), `fzf` (Search), `bat` (Cat alternative), `eza` (Ls alternative).
    

---

## **5. Operational Workflows**

### **🧪 Workflow A: C Programming**

1. **Open VS Code** on Mac. Connect to `compute`.
    
2. **Terminal:** Type `lab` to enter Arch Linux.
    
3. **Navigate:** `z cs101` (Zoxide jump).
    
4. **Edit:** Write code in `src/main.c`.
    
5. **Run:** Type `make run` (Using your custom Makefile).
    

### **📐 Workflow B: Applied Math & Simulation**

1. **Start Engine:** Inside `lab` terminal, run:
    
    Bash
    
    ```
    jupyter lab --no-browser --ip=0.0.0.0 --port=8888
    ```
    
2. **Visualize:** Open `http://compute:8888` on Mac Safari.
    
3. **Render Video:**
    
    Bash
    
    ```
    manim -qm my_scene.py SceneName
    ```
    
4. **View:** Download the `.mp4` from the file explorer or sync via Syncthing.
    

### **🤖 Workflow C: AI Assistance**

- **Web:** Go to `http://compute:8080`. Select **Qwen 2.5 Coder**. Paste your C code for debugging.
    
- **Terminal:** Type `ai` (Alias for `podman exec -it ollama...`) for quick questions.
    
- **Automation:** Use **n8n** (`http://compute:5678`) to schedule daily math facts or summarize papers using the AI.
    

### **🎮 Workflow D: Gaming & Desktop**

1. **Host:** **Sunshine** is running as a system service.
    
2. **Client:** Open **Moonlight** on Mac/iPhone.
    
3. **Action:** Stream your full 4080 desktop at 120Hz/4K to your Mac.
    

---

## **6. Data Management & Backup**

### **Synchronization (Live)**

- **Tool:** Syncthing.
    
- **Path:** `~/University`
    
- **Behavior:** A file saved on Mac appears on PC and iPhone (Mobius Sync) instantly.
    

### **Backup (History)**

- **Tool:** Git + GitHub.
    
- **Routine:** At the end of a study session:
    
    Bash
    
    ```
    cd ~/University
    git add .
    git commit -m "Progress update"
    git push
    ```
    

---

## **7. Maintenance Procedures**

### **Weekly Updates**

Run this single command on the **Bazzite Host** to update the OS, The Lab, and the AI:

Bash

```
update-all
```

### **Troubleshooting Cheat Sheet**

- **"Command not found":** Are you in the right place?
    
    - `podman` commands run on **Host**.
        
    - `gcc`/`python` commands run in **Lab**.
        
- **"Connection Refused":**
    
    - Check Firewall: `sudo firewall-cmd --list-ports`.
        
    - Check Service: `podman ps`.
        
- **"AI not responding":**
    
    - Restart it: `podman restart ollama open-webui`.
        

Status: Your lab is fully operational.

Current Mission: Study. 🚀