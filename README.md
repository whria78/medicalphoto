# MedicalPhoto Installation Manual
MedicalPhoto is a non-commercial medical image management program developed primarily for dermatologists, but it can also be used by plastic surgeons and dentists. Originally designed for dermatology at Asan Medical Center in 2003, MedicalPhoto helps manage the 200–300 clinical photos captured daily. With its built-in database, users can locate images in under a second. The program supports ICD-10 diagnosis, user-defined diagnoses, multiple monitors, and a server-client structure for multi-computer access.

![Screeshot](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_11.png)

## Features
- Simple and easy to use
- Network support (server-client structure)
- Dual/multiple monitor support
- Built-in ICD-10 and dermatologic diagnosis database
- Customizable diagnoses and procedure tagging

---

## Installation
### 1. Server Side Installation
#### 1.1 Install Server
Run the installer (`Setup.exe`). In the "Select Type" section, choose:
- **"Server and Client"** if this is the first-time installation.
- **"Client"** if the server is already installed.

![Installation Type Selection](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_12.png)

![Setup Window](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_1.png)

After installation, the configuration wizard will launch automatically.

#### 1.2 Configuration

![Configuration](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_5.png)

- Select the main directory where photos will be saved. Specify a location with sufficient storage capacity.
- If the folder contains previously taken photos, MedicalPhoto will gather their information. This process may take time depending on the number of photos.

#### 1.3 Check IP Address

![Check IP Address](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_15.png)

- "MedicalPhotoServer" appears as an icon in the system tray.

![Server Monitoring](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_22.png)

- It is a server-monitoring tool displaying the **[IP Address]** upon startup.
- The **[Host Address]** is the internal IP address of the server.
- Clients must use this IP address to connect.

---

## 2. Client Side Installation
Before installing a client, the MedicalPhoto server must be installed.

- Run `Setup.exe` on the client computer.
- Select **"Client"** in the "Select Type" menu.
- Enter the **[IP Address]** of the server.
- You can later change the IP in **"Preference" → "Server Information"**.

---

## Client Usage

### 2.0 Connect to the Server

Default password is '0000'.
The password can be changed at 'C:/medicalphoto/s_config.txt'

### 2.1 Client Window Components

![Client Window](https://github.com/whria78/medicalphoto/blob/master/docs/imgs/image_23.png)

- **Search Box** (Shortcut: `F12`)
- **Folder Tree**
- **Patient Information Box**
- **Comment Box**
- **Photographic Listbox**

### 2.2 Search Photos
- Use fields: `[DX], [ICD], [NAME], [<], [>], [ID]`
- Use **"AND"** or **"OR"** for advanced search.
- Example: `tinea pedis AND smith`

### 2.3 Patient Information Box
- Includes **Diagnosis, ID, Name, Date**, and a **Submit** button.
- Enter a partial diagnosis name and press `Enter` to search.
- If the desired keyword is not in the built-in database, enter a custom diagnosis and click **Submit**.
- MedicalPhoto stores previously entered keywords.
- User-defined diagnoses can be edited in **"Preference" → "Custom Diagnosis"**.
- Pressing **Submit** renames the file based on diagnosis, patient’s name, ID, and date.

### 2.4 Comment Box
- Comments can be added but do not affect the filename.

### 2.5 Photographic Listbox
- **Left-click**: Select/deselect an image.
- **Ctrl + Click**: Selects all photos taken around the same time or with similar filenames.
- **Right-click**: Provides options like Download, Upload, Rename, Delete.
- **Double-click**: Opens the photo in full-screen mode.
  - Arrow keys: Rotate photos.
  - Spacebar: Zoom in.
  - PageUp/PageDown: Send photos to a secondary monitor.

### 2.6 Selected Photos Listbox
- Displays selected filenames.
- Files selected via **Ctrl + Click** appear in **red**.

---

## 3. Menu
### 3.1 View Mode (`Ctrl + T`)
- **Normal Mode**
- **Simple Mode** (for resolutions below `1024×768`)

### 3.2 Upload (`Ctrl + U`)
- Photos are stored in date-named folders (e.g., `2007/2007-01/07-01-24`).
- If EXIF data is missing, photos are placed in the **"Unknown Date"** folder.

### 3.3 User Diagnosis
- User diagnoses are shared across all clients.

### 3.4 Preferences
- **General**: Enable/disable filename automation.
- **Server Information**: Displays server IP.
- **Search Options**: Modify search behavior.
- **Diagnosis Files**: Includes built-in **`derma.dat`** (dermatology diagnosis and ICD-10 database).

---

## 4. Uploading & Downloading Photos
- Use the **Upload-Ex** menu button for easy photo uploads.

---

## 5. Keyboard Shortcuts
| Shortcut       | Action |
|---------------|--------|
| `F12`         | Focus on search box |
| `Ctrl + E`    | Focus on diagnosis box |
| `Ctrl + A`    | Select all |
| `Ctrl + Click`| Select time-related photos |
| `Ctrl + D`    | Download |
| `Ctrl + U`    | UploadEx |
| `Double-click`| Full-screen view |
| `ESC`         | Deselect all |

**Full-Screen Mode:**
| Shortcut   | Action |
|------------|--------|
| `PageUp`   | Move photo to next monitor |
| `PageDown` | Move photo to previous monitor |
| `Space`    | Zoom in |
| `E, R`     | Rotate image |
| `← →`      | Navigate images |
| `ESC`      | Close window |

---

## 6. Server Management
The server consists of:
- **`MedicalPhotoServer`** (server monitor)
- **`console.exe`** (server core running as a Windows service)

### 6.1 Server Functions
- **Start Server**: Launches `console.exe` in the background.
- **Stop Server**: Stops `console.exe`.
- **Options**: Configure the server.
- **Check Database**: Ensures consistency between the database and photo files.
- **Log Window**: Displays the **Host IP Address** and application version.

---

## 7. Security
- A security password can be set in **`s_config.txt`** (`ADMIN_PASS=1234`).

---

## 8. Troubleshooting
- Report bugs to **whria78@gmail.com**.

---

## 9. Copyright
GPL license and Free for all purpose

## Old repo
http://medicalphoto.sf.net
http://medieye.sf.net

## Requirements
- **VC2015**
- **Boost 1.61**
