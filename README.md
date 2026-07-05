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

## 📂 Repository-Struktur & CAD-Modelle

Die aktuelle CAD-Entwicklung findet Cloud-basiert statt. Das interaktive 3D-Modell kann direkt im Browser eingesehen werden:
👉 **[OpenFuselage-UAV auf Onshape ansehen](https://cad.onshape.com/documents/8b250d0c03d7a3b609c8d7fb/w/4129f33a8aafaadd1a6fb501/e/e16a9e18ad5e6c49e04cec56)**

```text
├── mechanical/            # Lokale Exporte der 3D-CAD-Modelle (STEP, STL)
├── simulation/            # Webots-Welten und Drohnen-Modelle (PROTO-Dateien)
├── config/                # ArduPilot Parameter-Dateien (.param) für das Tuning
├── docs/                  # Aerodynamische Analysen, Berechnungen und Testergebnisse
└── README.md              # Diese Datei
