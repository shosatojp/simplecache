python3 setup.py sdist
rm -rf *.egg-info build
twine upload dist/*
rm -rf dist/
