{
  "targets": [
    {
      "target_name": "fcntl",
      "sources": [ "src/fcntl.cpp" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}