This plugin adds a simple HTTP server that informs about the progress
of simulations. It servers as an example. Nevertheless, you can 
use it in your application as well.

Usage
-----
    
    /app/plugin/load libhttpPlugin.so

Implementation details
----------------------
- Based on W++ library (see https://github.com/konteck/wpp)
- The HTTP server runs in a separate thread (pthreads library).

URLs
----
- **/** : default page with links to others
- **/eventNumber** : the number of the last processed event
- **/configuration** : complete listing of configuration values (see g4::Configuration)
- **/scoring** : a list of scoring meshes (if they are used at all). *In progress*

Configuration
-------------
- **http.port** : which port the server will run on (default 7070)