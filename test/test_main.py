import sys
import unittest

sys.path.append("..")
from src.main import main


class TestMain(unittest.TestCase):

    def test_main(self):
        self.assertEqual(main(), "Hello, World!", "Return value shuld be Hello, World!")
        self.assertEqual(main(), "abc-123", "Return value shuld be Hello, World!")
        


if __name__ == "__main__":
    unittest.main()