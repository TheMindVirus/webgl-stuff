from http.server import *
HTTPServer(("0.0.0.0", 9090), SimpleHTTPRequestHandler).serve_forever()
