# 1. BASE LAYER: Start with the heaviest dependency (CUDA + PyTorch)
FROM pytorch/pytorch:2.0.1-cuda11.7-cudnn8-devel
# Add this environment variable line before your apt-get commands
ENV DEBIAN_FRONTEND=noninteractive
# 2. SYSTEM DEPENDENCIES (Compilers, Tools, Graphics libs for OpenCV)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    libgtk2.0-dev \
    pkg-config \
    libopenblas-dev \
    liblapack-dev \
    libx11-dev

# 3. LIBRARIES FROM APT (Stable versions)
# Installs: Boost, Eigen3, Armadillo, Dlib, mlpack
RUN apt-get install -y \
    libboost-all-dev \
    libeigen3-dev \
    libarmadillo-dev \
    libdlib-dev \
    libmlpack-dev

# 4. OPENCV (Install from Source to get CUDA support)
# We build it from source to ensure it uses the container's CUDA and Eigen
WORKDIR /tmp
RUN git clone https://github.com/opencv/opencv.git && \
    git clone https://github.com/opencv/opencv_contrib.git && \
    cd opencv && mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -D OPENCV_EXTRA_MODULES_PATH=/tmp/opencv_contrib/modules \
          -D WITH_CUDA=ON \
          -D WITH_CUDNN=ON \
          -D OPENCV_DNN_CUDA=ON \
          -D WITH_EIGEN=ON \
          -D WITH_V4L=ON \
          -D BUILD_opencv_python3=OFF \
          .. && \
    make -j$(nproc) && make install && \
    cd / && rm -rf /tmp/opencv*

# 5. SHARK LIBRARY
# Fixes: 
# 1. Corrects the broken URL (removes the Markdown brackets).
# 2. Adds --recursive to download the 'Remora' linear algebra submodule (CRITICAL).
# 3. Adds libhdf5-dev dependency which Shark often needs.
RUN apt-get update && apt-get install -y libhdf5-dev && \
    git clone --recursive https://github.com/Shark-ML/Shark.git /tmp/Shark && \
    cd /tmp/Shark && \
    mkdir build && cd build && \
    cmake -D BUILD_EXAMPLES=OFF \
          -D BUILD_TESTING=OFF \
          -D ENABLE_HDF5=ON \
          .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/Shark
# # 6. CAFFE (The trickiest one - Optional)
# # Caffe is very old (pre-2017). Unless you strictly need it for legacy code,
# # I HIGHLY recommend skipping it. It conflicts with modern cuDNN.
# # If you MUST have it, use the specialized 'caffe:gpu' image separately.

# Final setup
# 7. CREATE & SWITCH USER
# Use the same User ID (UID) and Group ID (GID) as your host machine (usually 1000)
ARG USER_ID=1000
ARG GROUP_ID=1000

RUN groupadd -g ${GROUP_ID} ethanli && \
    useradd -m -u ${USER_ID} -g ethanli -s /bin/bash ethanli && \
    # Give sudo access (optional but useful for dev)
    usermod -aG sudo ethanli && \
    echo "ethanli ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set the active user
USER ethanli
WORKDIR /workspace
CMD ["/bin/bash"]
