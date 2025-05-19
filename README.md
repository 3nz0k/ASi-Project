# Application Banc de Test AS-i avec Interface Graphique

## 📦 Description

Cette application, développée en **C++**, permet de tester des **distributeurs AS-i** via une **interface graphique intuitive**. Elle intègre également une fonctionnalité de lecture et d’écriture sur des **tags RFID**, offrant ainsi une solution complète pour le diagnostic et la configuration de modules industriels.

---

## 🎯 Fonctionnalités

- 🧪 Test des distributeurs AS-i
- 🖥️ Interface graphique ergonomique (GUI)
- 📡 Lecture de tags RFID
- ✍️ Écriture sur tags RFID
- 🔄 Communication avec bus AS-i pour vérification en temps réel
- 📃​ Fichier de configuration pour définir les bits d'ouverture et de fermeture des vannes

---

## 🛠️ Technologies utilisées

- **Langage** : C++
- **Compilateur** : [MinGW32](http://www.mingw.org/)
- **Interface graphique** : Qt
- **Communication AS-i** : Asidrv32
- **RFID** : Winscard

---

## 📷 Aperçu de l'application

[Fenêtre Principale](https://github.com/user-attachments/assets/61aa86e3-d01e-47fb-8bd8-414c26408300)
[Test Manuel du distributeur](https://github.com/user-attachments/assets/6370b19d-57ea-41f5-851f-c7a60b463544)
[Test Automatique du distributeur](https://github.com/user-attachments/assets/a273a1c6-6a9f-40ac-b20b-bb8c8ed0ff18)
[Lecture d'un tag RFID](https://github.com/user-attachments/assets/609351d1-dba9-486f-8ad2-8fbbda2e624f)
[Création d'un tag RFID](https://github.com/user-attachments/assets/93932c9f-07a0-471d-8549-d19eb7aa83ce)

---

## 🚀 Installation

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/3nz0k/BancTestASi.git
   cd BancTestASi
   ```

2. Compiler le programme avec mingw32
   ```bash
   mingw32-make
   ```
