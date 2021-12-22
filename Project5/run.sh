#!/bin/bash -v
javac Buffer.java
javac Producer.java
javac Consumer.java
javac Coordinator.java
java Coordinator 10 18 3 1 4
