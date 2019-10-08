FROM buildpack-deps:stretch
RUN apt-get update \
 && apt-get install -y --no-install-recommends bison gcovr flex libev-dev libev4 libjansson-dev libjansson4 libprotobuf-c-dev libprotobuf-c1 \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/* || true
