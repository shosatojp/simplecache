# simplecache

![C/C++ CI](https://github.com/shosatojp/simplecache/workflows/C/C++%20CI/badge.svg)

Chrome(Linux,Android) cache extractor.

## Usage

### Get list of cache

```sh
simplecache --cache ~/.cache/google-chrome/Default/Cache/ --list
```

### Save cached file

```sh
simplecache --cache ~/.cache/google-chrome/Default/Cache/ --key https://example.com/image.png --out myimage.png
```

### Options

```sh
[usage]
simplecache [OPTIONS]
--list  -l      list all keys
--cache -c      cache directory
--key   -k      key
--out   -o      output path
```

### Python Binding

```py
import simplecache
```

## install

download artifacts from [here](https://github.com/shosatojp/simplecache/actions) or manually build.

## build

### build on host

```sh
sudo apt-get install -y g++ python3.8-dev make python3-pip
pip3 install pybind11
make
```

### build with docker

```sh
sudo docker-compose up --build
```

* specify python version in `docker-compose.yml` (default python3.8)
