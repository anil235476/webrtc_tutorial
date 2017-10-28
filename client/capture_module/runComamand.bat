setx WEBRTC_DIR "D:\webrtcBuild\Sept\webrtc_checkout\src"

echo %WEBRTC_DIR%

setx WEBRTC_LIB_DIR "D:\webrtcBuild\Sept\webrtc_checkout\src\out\Default\obj"

echo %WEBRTC_LIB_DIR%

cmake ../
