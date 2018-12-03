import unittest
import sys
sys.path.insert(0, '/autograder/gradescope_utils/gradescope_utils/autograder_utils')
from files import check_submitted_files
from decorators import weight
from decorators import visibility
from decorators import number
import subprocess as sp
import os.path
import time
from ee200utils import *

wdir = '/autograder/build/array/'

def test_build(test, target):
  try:
    log = sp.check_output(["make", "-f", wdir + "test_makefile", "--silent", "--always-make", "-C", wdir, target], stderr = sp.STDOUT)

  except CalledProcessError as e:
    test.fail("Failed to compile. g++ output is: {}".format(e.output.decode('utf-8')))

  if len(log.strip()) > 0:
    print("g++ output:\n{}".format(log.decode('utf-8')))

  # check that the output exists
  val = os.path.isfile(wdir + target)
  test.assertTrue(val, "Make/g++ didn't produce a binary")

  # Otherwise, we're all good
  print('Compiled successfully!')

def run_valgrind(test, target):
  try:
    log = sp.check_output(["valgrind", "--tool=memcheck", "--leak-check=yes", "--error-exitcode=4", wdir + target], stderr = sp.STDOUT)

  except CalledProcessError as e:
    test.fail("Valgrind reported errors:\n {}".format(e.output.decode('utf-8')))

  print("Valgrind clean!")


class TestArrays(unittest.TestCase):
    longMessage = False # Override default error messages

    # Test whether all files have been submitted
    @weight(1)
    @visibility('visible')
    @number('1')
    def test01_submitted_files(self):
        """Check submitted files"""
        missing_files = check_submitted_files([wdir + 'array.h', wdir + 'test_array.cpp'])
        for path in missing_files:
            print('Missing {0}'.format(path))
        self.assertEqual(len(missing_files), 0, 'Missing some required files for problem 1!')
        print('All required files submitted!')

    # Test whether submitted files compile successfully
    # The student may have submitted a Makefile, so don't clobber it
    # Just point Make to our (differently-named) file
    @weight(1)
    @visibility('visible')
    @number('2')
    def test02_compilation(self): 
        """Test compilation with test_array.cpp"""
        # Try to build student code
        test_build(self, "student_test")

    @weight(1)
    @visibility('visible')
    @number('3')
    def test03_exception(self): 
        """Compile exception"""
        test_build(self, "test_outofbounds")

    # Test functionality of student code
    # Also test for memory leaks where appropriate
    @weight(5)
    @visibility('after_published')
    @number('4')
    def test04_outofbounds(self): 
        """test out of bounds exception"""
        test_build(self, "test_outofbounds")
        result = safe_run(self, wdir + 'test_outofbounds')
        result = findString(result)
        self.assertEqual(result, "PASS", result)
        print("Test passed!")
    
    @weight(5)
    @visibility('after_published')
    @number('5')
    def test05_fail_during_append(self): 
        """malloc/new fails during append()"""
        test_build(self, "test_fail_during_append")
        result = safe_run(self, wdir + 'test_fail_during_append')
        result = findString(result)
        self.assertEqual(result, "PASS", result)
        print("Test passed!")

    @weight(3)
    @visibility('after_published')
    @number('6')
    def test06_fail_during_append_valgrind(self): 
        """Test with valgrind"""
        run_valgrind(self, 'test_fail_during_append')
    
    @weight(5)
    @visibility('after_published')
    @number('7')
    def test07_fail_during_append_array(self): 
        """malloc/new fails during append(array)"""
        test_build(self, "test_fail_during_append_array")
        result = safe_run(self, wdir + 'test_fail_during_append_array')
        result = findString(result)
        self.assertEqual(result, "PASS", result)
        print("Test passed!")

    @weight(3)
    @visibility('after_published')
    @number('8')
    def test08_fail_during_append_array_valigrind(self): 
        """Test with valgrind"""
        run_valgrind(self, 'test_fail_during_append_array')
    
    @weight(5)
    @visibility('after_published')
    @number('9')
    def test09_fail_during_assignment(self): 
        """Test malloc/new fails during assignment"""
        test_build(self, "test_fail_during_assignment")
        result = safe_run(self, wdir + 'test_fail_during_assignment')
        result = findString(result)
        self.assertEqual(result, "PASS", result)

    @weight(3)
    @visibility('after_published')
    @number('10')
    def test10_fail_during_assignment_valgrind(self): 
        """Test with valgrind"""
        run_valgrind(self, 'test_fail_during_assignment')

