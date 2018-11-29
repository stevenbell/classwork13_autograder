import sys
sys.path.insert(0, '/autograder/gradescope_utils/gradescope_utils/autograder_utils')
import unittest
from json_test_runner import JSONTestRunner

if __name__ == '__main__':
    suite = unittest.defaultTestLoader.discover('tests')
    JSONTestRunner(visibility='visible', stdout_visibility='visible').run(suite)
