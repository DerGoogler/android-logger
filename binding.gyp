{
	"targets": [
		{
			"target_name": "__native_logger",
			"include_dirs": [
				"<!(sh -c \"echo \$PREFIX/include\")",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
			"sources": [
      	"logger.cpp"
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}