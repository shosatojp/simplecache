python3 setup.py sdist
rm -rf *.egg-info build
pip3 install $(find dist -type f)
rm -rf dist
