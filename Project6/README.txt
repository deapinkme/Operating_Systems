README
======
Andrea M. Stojanovski

A. This package includes the following files:

|-- docker-compose.yml [as requested in assignment]
|-- README.txt [This file]

|-- client [as requested in assignment]
  |-- Dockerfile [as requested in assignment]
  |-- requirements.txt [as requested in assignment]
  |-- app [as requested in assignment]
    |-- client.py [as requested in assignment]

|-- server [as requested in assignment]
  |-- Dockerfile [as requested in assignment]
  |-- requirements.txt [as requested in assignment]
  |-- app [as requested in assignment]
    |-- server.py [as requested in assignment]

B. Answer the following questions:

1. What is a docker container?
  A docker container is used to encapsulate everything an application would need to run. This allows the developers to work in a standardized enviornment.

2. What is the difference between a container and a virtual machine?
  Containers: provide ways to virtualize an OS (not multiple OS, but can do multiple workloads on one OS).
  VM: hardware is virtualized to run multiple OS instances.

3. What is the purpose of a Dockerfile?
  A Dockerfile is used to manage all the commands a user can call on command line in a single text document.

4. What is the purpose of a requirements.txt file?
  This is used to manage what python packages are necessary and used in order to run the app.

5. What is the purpose of a docker-compose.yml file?
  This is used to deploy, combine and configure multiple Docker containers simultaniously.

6. What is the difference between a docker image and docker container?
  Docker image: used to build containers (read-only templates).
  Docker container: deploted instances created for Docker images.

7. What command can be used to create an image from a Dockerfile?
  $ docker image build [OPTIONS] PATH | URL | -

8. What command will start a docker container?
  $ docker start [OPTIONS] CONTAINER [CONTAINER...]

9. What command will stop a docker container? 
  $ docker stop [OPTIONS] CONTAINER [CONTAINER...]

10. What command will remove a docker container? Image?
  $ docker system prune
  Docker uses the same line to clean up all resources, including images, containers, volumes, and networks.

11. What command will list all running docker containers? all containers?
  $ docker container ls
  This will list running containers.
  $ docker container ls -a
  This will list all containers (due to the -a).

12. What command will list all docker images?
  $ docker image ls
  This will list all docker images. This also will show you the size of the images.

13. What command do you use to deploy docker containers using information in the
docker-compose.yml file?
  $ docker app render --output docker-compose.yml hello-world.dockerapp
  This deploys docker containers using information in the docker-compose.yml file.

14. How can you specify in the docker-compose.yml file that you want docker containers
to use the hosts network?
  $ curl http://localhost:5000
  Uses local host 5000.

15. How can you specify in the docker-compose.yml file where the Dockerfile for a
particular container is found?
  $ docker-compose [-f <arg>...] [--profile <name>...] [options] [COMMAND] [ARGS...]
  example:
  $ docker-compose -f docker-compose.yml -f docker-compose.admin.yml run backup_db
  This specifies multiple compose files.