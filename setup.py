#!/usr/bin/env python

from distutils.core import setup

setup(name='weasel',
      version='0.3',
      py_modules=['weasel', 'toolbox'],
      packages=['gui', 'structure', 'templates.glom','templates.golgi','templates.granule'],
      )
