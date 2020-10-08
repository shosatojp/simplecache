# simplecache

![C/C++ CI](https://github.com/shosatojp/simplecache/workflows/C/C++%20CI/badge.svg)

Chrome(Linux,Android) cache extractor.

## Usage

```sh
[usage]
simplecache [OPTIONS]
--list  -l      list all keys
--cache -c      cache directory
--key   -k      key
--out   -o      output path
```

### Get list of cache

```sh
simplecache --cache ~/.cache/google-chrome/Default/Cache/ --list
```

### Save cached file

```sh
simplecache --cache ~/.cache/google-chrome/Default/Cache/ --key https://example.com/image.png --out myimage.png
```

## Python Binding

```sh
pip install chromesimplecache
```

```py
from simplecache import SimpleCacheEntry
import glob
import urllib.parse
import os
import brotli
import gzip
import zlib

cache_dir = os.path.expanduser('~/.cache/google-chrome/Default/Cache/*_0')
out_dir = 'cache'

if not os.path.exists(out_dir):
    os.mkdir(out_dir)

for entry_file in glob.glob(cache_dir):
    e = SimpleCacheEntry(entry_file)
    url = e.get_key()
    print(url)

    filename = urllib.parse.quote(url, safe='')[:255]
    encoding = e.get_header().headers.get('content-encoding', '').strip().lower()
    out_path = os.path.join(out_dir, filename)

    if encoding:
        # decompress with python
        data = e.get_data()
        if encoding == 'gzip':
            data = gzip.decompress(data)
        elif encoding == 'br':
            data = brotli.decompress(data)
        elif encoding == 'deflate':
            data = zlib.decompress(data)

        with open(out_path, 'wb') as f:
            f.write(data)
    else:
        # faster for binary
        e.save(out_path)
```

## Install

Download artifacts from [here](https://github.com/shosatojp/simplecache/actions) or manually build.

## Build

### Build on host

```sh
sudo apt-get install -y g++ python3.8-dev make python3-pip
pip3 install pybind11
make
```

### Build with docker

```sh
sudo docker-compose up --build
```

* Specify python version in `docker-compose.yml` (default python3.8)
