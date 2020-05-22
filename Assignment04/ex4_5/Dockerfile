##########################################################################################
#
# Docker container for ParaView 5.8.0 with VNC and SSH support.
#
# Starting the image/container will automatically run:
#     - SSH server on port 22
#     - VNC server on port 5920
# User name is 'root', password 'docker' for both SSH and VNC.
#
# Starting the image/container will offer you a shell where you can directly launch
# ParaView.
#     > ./paraview
# Note that no window is displayed. Connect to the VNC server with your favourite VNC
# client to interact with the ParaView window.
#
# Exiting the shell will stop the container.
#
# See second box for instructions on how to build, load, and run the image or container
# with Docker.
#
##########################################################################################
#
# (1) Build this docker image by first loading ParaView 5.8.0, then building the image
#     itself.
#     > docker load -i /path/to/paraview-5.8.0.docker
#     > docker build -t scivis-2020:sheet-4 /path/to/this/Dockerfile
#
# (2) Initialize the container by running the docker image.
#     > docker run -p 5000:22 -p 5920:5920 --name scivis_sheet_4 -it scivis-2020:sheet-4
#
# (3) After running it, the container can always be restarted. This way, modifications
#     are preserved, e.g., after compiling and adding the plugin to ParaView.
#     > docker start -ia scivis_sheet_4
#
# (4) To reset to the container to its original state, remove it and proceed with (2).
#     > docker container rm scivis_sheet_4
#
##########################################################################################
FROM paraview:5.8.0
LABEL description="Scientific Visualization: Assignment 04"

# hotfix for CMake path
RUN sed -i 's/paraview-5.6/paraview-5.8/' /root/.bashrc

# hotfix for x11vnc crashes
RUN apt-get install -y pkg-config autoconf libssl-dev libvncserver-dev libxtst-dev && \
    apt-get remove -y x11vnc && \
    mkdir -p /root/x11vnc-src && \
    cd /root/x11vnc-src && \
    git clone --branch 0.9.16 --depth 1 https://github.com/LibVNC/x11vnc.git . && \
    autoreconf -fiv && \
    ./configure && \
    make && make install && \
    rm -rf /root/x11vnc-src && \
    echo "screen -wipe > /dev/null" >> /root/.bashrc && \
    echo "if [ \$(screen -ls | grep vnc | wc -l) == 0 ]; then screen -dmS vnc /root/.start_vnc.sh; fi" >> /root/.bashrc

# get and configure assignment code
ENV CMAKE_PREFIX_PATH /root/paraview/lib/cmake/paraview-5.8
RUN mkdir -p /root/scivis-2020/source /root/scivis-2020/build /root/scivis-2020/install && \
    cd /root/scivis-2020/source && \
    wget --no-check-certificate https://cloud.visus.uni-stuttgart.de/index.php/s/Pl3l9QH727Rtg00/download -O common.zip && \
    wget --no-check-certificate https://cloud.visus.uni-stuttgart.de/index.php/s/qYspIizA4pdU0s3/download -O assignment_04.zip && \
    unzip common.zip && \
    unzip assignment_04.zip && \
    cd /root/scivis-2020/build && \
    cmake -DCMAKE_INSTALL_PREFIX=/root/scivis-2020/install /root/scivis-2020/source && \
    make install

# start VNC and ParaView when running the docker image
ENTRYPOINT ["/root/.startup.sh"]
