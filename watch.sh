
#!/usr/bin/env bash
set -u
find src include tests -name '*.cpp' -o -name '*.hpp' | \
  entr -c sh -c 'cmake --build build && ctest --test-dir build --output-on-failure'
