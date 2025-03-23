  #!/bin/bash
  cat "${INPUT_FILENAME}" | tr -d '\r' | ./${ZIP_NAME}/"${EXECUTABLE_NAME}"
