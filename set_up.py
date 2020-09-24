from distutils.core import setup
from Cython.Build import cythonize

setup(
    ext_modules = cythonize("load_files.pyx")
)

