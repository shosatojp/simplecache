from simplecache import SimpleCacheEntry
import glob
import urllib.parse
import os

cache_dir = os.path.expanduser('~/.cache/google-chrome/Default/Cache/*_0')
out_dir = 'cache'

if not os.path.exists(out_dir):
    os.mkdir(out_dir)

for entry_file in glob.glob(cache_dir):
    e = SimpleCacheEntry(entry_file)
    key = e.get_key()

    path = urllib.parse.urlparse(key).path
    _, filename = os.path.split(path)
    out_path = os.path.join(out_dir, filename)

    e.save(out_path)
