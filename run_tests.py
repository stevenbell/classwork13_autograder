import sys
sys.path.insert(0, '/autograder/gradescope_utils/gradescope_utils/autograder_utils')
import json
import unittest
from json_test_runner import JSONTestRunner

if __name__ == '__main__':
    suite = unittest.defaultTestLoader.discover('tests')

    # Normally test cases are only visible after the due date
    # The submitted files / build cases are individually set to be visible, which overrides this
    vis = 'after_due_date'

    # But if this is a resubmission assignment, then make all the test cases visible
    metadata = json.load(open('/autograder/submission_metadata.json'))
    if metadata['assignment']['title'].endswith('resubmission'):
      vis = 'visible'

    JSONTestRunner(visibility=vis, stdout_visibility='visible').run(suite)

