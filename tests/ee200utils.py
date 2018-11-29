import re
from subprocess import *
import signal

# Small functions that get used repeatedly in creating and running tests
# on student C/C++ code.

def safe_run(test, command, timeout=5, **kwargs):
    """ Wrapper around check_output which fails the test if the code segfaults or
        takes too long.  A brief informative message is logged with the failure."""
    try:
        result = check_output(command, timeout=timeout, **kwargs)

    except CalledProcessError as e:
        if e.returncode == -signal.SIGSEGV:
            test.fail("Program segfaulted")
        else:
            # We don't know what students will return from main, so assume
            # anything other than a segfault is ok.
            result = e.output
    except TimeoutExpired as e:
            test.fail("Program timed out after {} seconds".format(timeout))

    return result.decode('utf-8')

def harness_run(test, command, timeout=5, **kwargs):
    """Equivalent to safe_run, except that it prints different error messages.
       This function should be used for all test harness code, while safe_run
       should be used any time we're calling student code."""
    try:
        result = check_output(command, timeout=timeout, **kwargs)

    except CalledProcessError as e:
        if e.returncode == -signal.SIGSEGV:
            test.fail("Test harness segfaulted - check with teaching staff")
        else:
            test.fail("Test harness call failed - check with teaching staff")
    except TimeoutExpired as e:
            test.fail("Test harness timed out - check with teaching staff")

    return result.decode('utf-8')


def findString(haystack):
    matches = re.findall('###.*###', haystack)

    # There should be exactly one match, or we're hosed
    if len(matches) != 1:
        return None

    # Strip off the ###
    return matches[0][3:-3]



