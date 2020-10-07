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
