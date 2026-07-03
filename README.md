# OpenFuselage-UAV

Dieses Repository enthält die Entwicklungsdaten, 3D-Modelle und Simulationen für ein **bahnbrechendes, neues Drohnen-Fuselage- und Airframe-Konzept**. Das Ziel dieses Open-Source-Projekts ist es, durch ein neuartiges aerodynamisches Design die Effizienz, Flugzeit und Stabilität von unbemannten Luftfahrzeugen (UAVs) drastisch zu verbessern.

---

## 🚀 Das Konzept: Aerodynamische Revolution

Klassische Multicopter-Rahmen sind oft aerodynamisch ineffizient und erzeugen bei Vorwärtsfahrt hohen Luftwiderstand. Dieses Projekt bricht mit traditionellen Designs:
- **Neuartiges Rumpfdesign (Fuselage):** Minimierung des Luftwiderstands bei hohen Geschwindigkeiten.
- **Aktive Aerodynamik / Strömungsoptimierung:** Nutzung des Luftstroms zur Generierung von zusätzlichem Auftrieb oder zur Stabilisierung, ohne die Motoren extra zu belasten.
- **Modulares Frame-Design:** Leichtgewichtig, robust und optimiert für den 3D-Druck oder die CNC-Fräsung.

---

## 💻 Software & Ökosystem

Wir erfinden das Rad nicht neu, sondern bauen auf dem verlässlichsten Industriestandard auf:
- **Firmware:** Das Projekt basiert vollständig auf **[ArduPilot](https://ardupilot.org/)** (ArduCopter/ArduPlane). Wir nutzen die mächtige Sensorfusion (EKF3) und die flexiblen Tuning-Möglichkeiten von ArduPilot, um die neuen aerodynamischen Eigenschaften optimal zu regeln.
- **Anpassungen:** Im Repository werden spezifische Parameter-Dateien (`.param`) und ggf. Custom-Code-Erweiterungen für ArduPilot bereitgestellt, die auf dieses spezielle Airframe-Verhalten abgestimmt sind.

---

## 🕹️ Simulation (SITL)

Da echte Prototypen-Abstürze teuer sind, setzen wir voll auf Simulationen. Um den Einstieg für Entwickler so einfach wie möglich zu gestalten, nutzen wir **Webots** als primäre Simulationsumgebung.

Unter den großen Plattformen (Gazebo / Webots / O3DE) wurde **Webots** bewusst gewählt, weil es:
1. Die **einfachste und leichtgewichtigste** Installation und Konfiguration bietet.
2. Hervorragende Out-of-the-Box-Physik für Propeller und aerodynamische Körper besitzt.
3. Perfekt mit dem ArduPilot SITL (Software-in-the-Loop) gekoppelt werden kann.

---

## 📂 Repository-Struktur

```text
├── mechanical/            # 3D-CAD-Modelle (STEP, STL) für den Rahmen
├── simulation/            # Webots-Welten und Drohnen-Modelle (PROTO-Dateien)
├── config/                # ArduPilot Parameter-Dateien (.param) für das Tuning
├── docs/                  # Aerodynamische Analysen, Berechnungen und Testergebnisse
└── README.md              # Diese Datei
```

---

## 🛠️ Mitmachen & Beitragen

Dieses Projekt lebt von der Community! Egal ob du Experte für Aerodynamik (CFD-Simulationen), Embedded-Entwickler für ArduPilot oder begeistert von 3D-Druck bist – jede Hilfe ist willkommen.

1. **Forke** das Repository.
2. Erstelle einen neuen Branch (`git checkout -b feature/NeuesFeature`).
3. Teste deine Änderungen in der **Webots-Simulation**.
4. Öffne einen **Pull Request**.

---

## 📄 Lizenz

Dieses Projekt ist unter der **GPL v3** lizenziert. Das bedeutet, dass alle Modifikationen und Weiterentwicklungen dieses Airframes ebenfalls als Open Source veröffentlicht werden müssen. Schützen wir gemeinsam die offene Entwicklung!
