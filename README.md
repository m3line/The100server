# Simulateur Réseau - Ark Crisis Control

Ce projet est un mini-simulateur de gestion de crise en temps réel basé sur une architecture **Client-Serveur TCP** en langage **C sous Linux**. Inspiré de l'univers de la série The 100, il simule le terminal de contrôle de Raven Reyes tentant de stabiliser les systèmes critiques de l'Ark à distance.

---

##  Fonctionnalités

* **Architecture Client-Serveur :** Communication bidirectionnelle via des sockets POSIX (TCP).
* **Transmission de structures brutes :** Sérialisation et envoi direct de structures de données (`struct`) à travers le réseau pour un suivi des jauges en temps réel.
* **Affichage Dynamique :** Interface en ligne de commande asynchrone avec rafraîchissement dynamique de l'écran (`system("clear")`) et alertes visuelles basées sur les codes couleurs ANSI.

---

##  Prérequis

L'application est conçue pour les systèmes de type Unix (Linux / macOS).
* Un compilateur `gcc`
* La bibliothèque standard POSIX pour les sockets

---

##  Compilation et Lancement

Pour faire tourner le projet: ouvrir **deux terminaux distincts** (un pour le serveur, un pour le client).
