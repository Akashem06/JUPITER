for log_file in build/unity_logs/*.txt; do
  if grep -q 'FAIL' "$log_file"; then
    echo "::error::Tests failed in $log_file. Check unity logs for details."
    exit 1
  fi
  if grep -q 'IGNORE' "$log_file"; then
    echo "::error::Tests ignored in $log_file. Check unity logs for details."
  fi
done