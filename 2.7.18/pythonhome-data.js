
  var Module = typeof Module !== 'undefined' ? Module : {};
  
  if (!Module.expectedDataFileDownloads) {
    Module.expectedDataFileDownloads = 0;
  }
  Module.expectedDataFileDownloads++;
  (function() {
   var loadPackage = function(metadata) {
  
      var PACKAGE_PATH;
      if (typeof window === 'object') {
        PACKAGE_PATH = window['encodeURIComponent'](window.location.pathname.toString().substring(0, window.location.pathname.toString().lastIndexOf('/')) + '/');
      } else if (typeof location !== 'undefined') {
        // worker
        PACKAGE_PATH = encodeURIComponent(location.pathname.toString().substring(0, location.pathname.toString().lastIndexOf('/')) + '/');
      } else {
        throw 'using preloaded data can only be done on a web page or in a web worker';
      }
      var PACKAGE_NAME = 'pythonhome.data';
      var REMOTE_PACKAGE_BASE = 'pythonhome.data';
      if (typeof Module['locateFilePackage'] === 'function' && !Module['locateFile']) {
        Module['locateFile'] = Module['locateFilePackage'];
        err('warning: you defined Module.locateFilePackage, that has been renamed to Module.locateFile (using your locateFilePackage for now)');
      }
      var REMOTE_PACKAGE_NAME = Module['locateFile'] ? Module['locateFile'](REMOTE_PACKAGE_BASE, '') : REMOTE_PACKAGE_BASE;
    
      var REMOTE_PACKAGE_SIZE = metadata['remote_package_size'];
      var PACKAGE_UUID = metadata['package_uuid'];
    
      function fetchRemotePackage(packageName, packageSize, callback, errback) {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', packageName, true);
        xhr.responseType = 'arraybuffer';
        xhr.onprogress = function(event) {
          var url = packageName;
          var size = packageSize;
          if (event.total) size = event.total;
          if (event.loaded) {
            if (!xhr.addedTotal) {
              xhr.addedTotal = true;
              if (!Module.dataFileDownloads) Module.dataFileDownloads = {};
              Module.dataFileDownloads[url] = {
                loaded: event.loaded,
                total: size
              };
            } else {
              Module.dataFileDownloads[url].loaded = event.loaded;
            }
            var total = 0;
            var loaded = 0;
            var num = 0;
            for (var download in Module.dataFileDownloads) {
            var data = Module.dataFileDownloads[download];
              total += data.total;
              loaded += data.loaded;
              num++;
            }
            total = Math.ceil(total * Module.expectedDataFileDownloads/num);
            if (Module['setStatus']) Module['setStatus']('Downloading data... (' + loaded + '/' + total + ')');
          } else if (!Module.dataFileDownloads) {
            if (Module['setStatus']) Module['setStatus']('Downloading data...');
          }
        };
        xhr.onerror = function(event) {
          throw new Error("NetworkError for: " + packageName);
        }
        xhr.onload = function(event) {
          if (xhr.status == 200 || xhr.status == 304 || xhr.status == 206 || (xhr.status == 0 && xhr.response)) { // file URLs can return 0
            var packageData = xhr.response;
            callback(packageData);
          } else {
            throw new Error(xhr.statusText + " : " + xhr.responseURL);
          }
        };
        xhr.send(null);
      };

      function handleError(error) {
        console.error('package error:', error);
      };
    
    function runWithFS() {
  
      function assert(check, msg) {
        if (!check) throw msg + new Error().stack;
      }
  Module['FS_createPath']('/', 'lib', true, true);
Module['FS_createPath']('/lib', 'python2.7', true, true);
Module['FS_createPath']('/lib/python2.7', 'json', true, true);
Module['FS_createPath']('/lib/python2.7', 'importlib', true, true);
Module['FS_createPath']('/lib/python2.7', 'encodings', true, true);
Module['FS_createPath']('/lib/python2.7', 'xml', true, true);
Module['FS_createPath']('/lib/python2.7/xml', 'etree', true, true);

      /** @constructor */
      function DataRequest(start, end, audio) {
        this.start = start;
        this.end = end;
        this.audio = audio;
      }
      DataRequest.prototype = {
        requests: {},
        open: function(mode, name) {
          this.name = name;
          this.requests[name] = this;
          Module['addRunDependency']('fp ' + this.name);
        },
        send: function() {},
        onload: function() {
          var byteArray = this.byteArray.subarray(this.start, this.end);
          this.finish(byteArray);
        },
        finish: function(byteArray) {
          var that = this;
  
          Module['FS_createDataFile'](this.name, null, byteArray, true, true, true); // canOwn this data in the filesystem, it is a slide into the heap that will never change
          Module['removeRunDependency']('fp ' + that.name);
  
          this.requests[this.name] = null;
        }
      };
  
          var files = metadata['files'];
          for (var i = 0; i < files.length; ++i) {
            new DataRequest(files[i]['start'], files[i]['end'], files[i]['audio']).open('GET', files[i]['filename']);
          }
  
    
        var indexedDB;
        if (typeof window === 'object') {
          indexedDB = window.indexedDB || window.mozIndexedDB || window.webkitIndexedDB || window.msIndexedDB;
        } else if (typeof location !== 'undefined') {
          // worker
          indexedDB = self.indexedDB;
        } else {
          throw 'using IndexedDB to cache data can only be done on a web page or in a web worker';
        }
        var IDB_RO = "readonly";
        var IDB_RW = "readwrite";
        var DB_NAME = "EM_PRELOAD_CACHE";
        var DB_VERSION = 1;
        var METADATA_STORE_NAME = 'METADATA';
        var PACKAGE_STORE_NAME = 'PACKAGES';
        function openDatabase(callback, errback) {
          try {
            var openRequest = indexedDB.open(DB_NAME, DB_VERSION);
          } catch (e) {
            return errback(e);
          }
          openRequest.onupgradeneeded = function(event) {
            var db = event.target.result;

            if(db.objectStoreNames.contains(PACKAGE_STORE_NAME)) {
              db.deleteObjectStore(PACKAGE_STORE_NAME);
            }
            var packages = db.createObjectStore(PACKAGE_STORE_NAME);

            if(db.objectStoreNames.contains(METADATA_STORE_NAME)) {
              db.deleteObjectStore(METADATA_STORE_NAME);
            }
            var metadata = db.createObjectStore(METADATA_STORE_NAME);
          };
          openRequest.onsuccess = function(event) {
            var db = event.target.result;
            callback(db);
          };
          openRequest.onerror = function(error) {
            errback(error);
          };
        };

        // This is needed as chromium has a limit on per-entry files in IndexedDB
        // https://cs.chromium.org/chromium/src/content/renderer/indexed_db/webidbdatabase_impl.cc?type=cs&sq=package:chromium&g=0&l=177
        // https://cs.chromium.org/chromium/src/out/Debug/gen/third_party/blink/public/mojom/indexeddb/indexeddb.mojom.h?type=cs&sq=package:chromium&g=0&l=60
        // We set the chunk size to 64MB to stay well-below the limit
        var CHUNK_SIZE = 64 * 1024 * 1024;

        function cacheRemotePackage(
          db,
          packageName,
          packageData,
          packageMeta,
          callback,
          errback
        ) {
          var transactionPackages = db.transaction([PACKAGE_STORE_NAME], IDB_RW);
          var packages = transactionPackages.objectStore(PACKAGE_STORE_NAME);
          var chunkSliceStart = 0;
          var nextChunkSliceStart = 0;
          var chunkCount = Math.ceil(packageData.byteLength / CHUNK_SIZE);
          var finishedChunks = 0;
          for (var chunkId = 0; chunkId < chunkCount; chunkId++) {
            nextChunkSliceStart += CHUNK_SIZE;
            var putPackageRequest = packages.put(
              packageData.slice(chunkSliceStart, nextChunkSliceStart),
              'package/' + packageName + '/' + chunkId
            );
            chunkSliceStart = nextChunkSliceStart;
            putPackageRequest.onsuccess = function(event) {
              finishedChunks++;
              if (finishedChunks == chunkCount) {
                var transaction_metadata = db.transaction(
                  [METADATA_STORE_NAME],
                  IDB_RW
                );
                var metadata = transaction_metadata.objectStore(METADATA_STORE_NAME);
                var putMetadataRequest = metadata.put(
                  {
                    'uuid': packageMeta.uuid,
                    'chunkCount': chunkCount
                  },
                  'metadata/' + packageName
                );
                putMetadataRequest.onsuccess = function(event) {
                  callback(packageData);
                };
                putMetadataRequest.onerror = function(error) {
                  errback(error);
                };
              }
            };
            putPackageRequest.onerror = function(error) {
              errback(error);
            };
          }
        }

        /* Check if there's a cached package, and if so whether it's the latest available */
        function checkCachedPackage(db, packageName, callback, errback) {
          var transaction = db.transaction([METADATA_STORE_NAME], IDB_RO);
          var metadata = transaction.objectStore(METADATA_STORE_NAME);
          var getRequest = metadata.get('metadata/' + packageName);
          getRequest.onsuccess = function(event) {
            var result = event.target.result;
            if (!result) {
              return callback(false, null);
            } else {
              return callback(PACKAGE_UUID === result['uuid'], result);
            }
          };
          getRequest.onerror = function(error) {
            errback(error);
          };
        }

        function fetchCachedPackage(db, packageName, metadata, callback, errback) {
          var transaction = db.transaction([PACKAGE_STORE_NAME], IDB_RO);
          var packages = transaction.objectStore(PACKAGE_STORE_NAME);

          var chunksDone = 0;
          var totalSize = 0;
          var chunkCount = metadata['chunkCount'];
          var chunks = new Array(chunkCount);

          for (var chunkId = 0; chunkId < chunkCount; chunkId++) {
            var getRequest = packages.get('package/' + packageName + '/' + chunkId);
            getRequest.onsuccess = function(event) {
              // If there's only 1 chunk, there's nothing to concatenate it with so we can just return it now
              if (chunkCount == 1) {
                callback(event.target.result);
              } else {
                chunksDone++;
                totalSize += event.target.result.byteLength;
                chunks.push(event.target.result);
                if (chunksDone == chunkCount) {
                  if (chunksDone == 1) {
                    callback(event.target.result);
                  } else {
                    var tempTyped = new Uint8Array(totalSize);
                    var byteOffset = 0;
                    for (var chunkId in chunks) {
                      var buffer = chunks[chunkId];
                      tempTyped.set(new Uint8Array(buffer), byteOffset);
                      byteOffset += buffer.byteLength;
                      buffer = undefined;
                    }
                    chunks = undefined;
                    callback(tempTyped.buffer);
                    tempTyped = undefined;
                  }
                }
              }
            };
            getRequest.onerror = function(error) {
              errback(error);
            };
          }
        }
      
      function processPackageData(arrayBuffer) {
        assert(arrayBuffer, 'Loading data file failed.');
        assert(arrayBuffer instanceof ArrayBuffer, 'bad input to processPackageData');
        var byteArray = new Uint8Array(arrayBuffer);
        var curr;
        
          // Reuse the bytearray from the XHR as the source for file reads.
          DataRequest.prototype.byteArray = byteArray;
    
            var files = metadata['files'];
            for (var i = 0; i < files.length; ++i) {
              DataRequest.prototype.requests[files[i].filename].onload();
            }
                Module['removeRunDependency']('datafile_pythonhome.data');

      };
      Module['addRunDependency']('datafile_pythonhome.data');
    
      if (!Module.preloadResults) Module.preloadResults = {};
    
        function preloadFallback(error) {
          console.error(error);
          console.error('falling back to default preload behavior');
          fetchRemotePackage(REMOTE_PACKAGE_NAME, REMOTE_PACKAGE_SIZE, processPackageData, handleError);
        };

        openDatabase(
          function(db) {
            checkCachedPackage(db, PACKAGE_PATH + PACKAGE_NAME,
              function(useCached, metadata) {
                Module.preloadResults[PACKAGE_NAME] = {fromCache: useCached};
                if (useCached) {
                  fetchCachedPackage(db, PACKAGE_PATH + PACKAGE_NAME, metadata, processPackageData, preloadFallback);
                } else {
                  fetchRemotePackage(REMOTE_PACKAGE_NAME, REMOTE_PACKAGE_SIZE,
                    function(packageData) {
                      cacheRemotePackage(db, PACKAGE_PATH + PACKAGE_NAME, packageData, {uuid:PACKAGE_UUID}, processPackageData,
                        function(error) {
                          console.error(error);
                          processPackageData(packageData);
                        });
                    }
                  , preloadFallback);
                }
              }
            , preloadFallback);
          }
        , preloadFallback);

        if (Module['setStatus']) Module['setStatus']('Downloading...');
      
    }
    if (Module['calledRun']) {
      runWithFS();
    } else {
      if (!Module['preRun']) Module['preRun'] = [];
      Module["preRun"].push(runWithFS); // FS is not initialized yet, wait for it
    }
  
   }
   loadPackage({"files": [{"filename": "/lib/python2.7/fnmatch.pyo", "start": 0, "end": 2347, "audio": 0}, {"filename": "/lib/python2.7/keyword.pyo", "start": 2347, "end": 4164, "audio": 0}, {"filename": "/lib/python2.7/ast.pyo", "start": 4164, "end": 11349, "audio": 0}, {"filename": "/lib/python2.7/io.pyo", "start": 11349, "end": 13417, "audio": 0}, {"filename": "/lib/python2.7/locale.pyo", "start": 13417, "end": 65221, "audio": 0}, {"filename": "/lib/python2.7/__future__.pyo", "start": 65221, "end": 67421, "audio": 0}, {"filename": "/lib/python2.7/collections.pyo", "start": 67421, "end": 84926, "audio": 0}, {"filename": "/lib/python2.7/colorsys.pyo", "start": 84926, "end": 88258, "audio": 0}, {"filename": "/lib/python2.7/dummy_thread.pyo", "start": 88258, "end": 91335, "audio": 0}, {"filename": "/lib/python2.7/tarfile.pyo", "start": 91335, "end": 151929, "audio": 0}, {"filename": "/lib/python2.7/linecache.pyo", "start": 151929, "end": 154566, "audio": 0}, {"filename": "/lib/python2.7/_abcoll.pyo", "start": 154566, "end": 174760, "audio": 0}, {"filename": "/lib/python2.7/base64.pyo", "start": 174760, "end": 182382, "audio": 0}, {"filename": "/lib/python2.7/genericpath.pyo", "start": 182382, "end": 184978, "audio": 0}, {"filename": "/lib/python2.7/shutil.pyo", "start": 184978, "end": 198439, "audio": 0}, {"filename": "/lib/python2.7/types.pyo", "start": 198439, "end": 200958, "audio": 0}, {"filename": "/lib/python2.7/hashlib.pyo", "start": 200958, "end": 207308, "audio": 0}, {"filename": "/lib/python2.7/abc.pyo", "start": 207308, "end": 211112, "audio": 0}, {"filename": "/lib/python2.7/UserDict.pyo", "start": 211112, "end": 220457, "audio": 0}, {"filename": "/lib/python2.7/traceback.pyo", "start": 220457, "end": 227887, "audio": 0}, {"filename": "/lib/python2.7/StringIO.pyo", "start": 227887, "end": 234181, "audio": 0}, {"filename": "/lib/python2.7/codecs.pyo", "start": 234181, "end": 254315, "audio": 0}, {"filename": "/lib/python2.7/repr.pyo", "start": 254315, "end": 259502, "audio": 0}, {"filename": "/lib/python2.7/difflib.pyo", "start": 259502, "end": 287135, "audio": 0}, {"filename": "/lib/python2.7/site.pyo", "start": 287135, "end": 300622, "audio": 0}, {"filename": "/lib/python2.7/urlparse.pyo", "start": 300622, "end": 311602, "audio": 0}, {"filename": "/lib/python2.7/functools.pyo", "start": 311602, "end": 316937, "audio": 0}, {"filename": "/lib/python2.7/gettext.pyo", "start": 316937, "end": 333965, "audio": 0}, {"filename": "/lib/python2.7/posixpath.pyo", "start": 333965, "end": 342569, "audio": 0}, {"filename": "/lib/python2.7/platform.pyo", "start": 342569, "end": 370339, "audio": 0}, {"filename": "/lib/python2.7/re.pyo", "start": 370339, "end": 376910, "audio": 0}, {"filename": "/lib/python2.7/_sysconfigdata.pyo", "start": 376910, "end": 377054, "audio": 0}, {"filename": "/lib/python2.7/_weakrefset.pyo", "start": 377054, "end": 386444, "audio": 0}, {"filename": "/lib/python2.7/sysconfig.pyo", "start": 386444, "end": 401328, "audio": 0}, {"filename": "/lib/python2.7/os.pyo", "start": 401328, "end": 416327, "audio": 0}, {"filename": "/lib/python2.7/dis.pyo", "start": 416327, "end": 421933, "audio": 0}, {"filename": "/lib/python2.7/sre_parse.pyo", "start": 421933, "end": 442817, "audio": 0}, {"filename": "/lib/python2.7/random.pyo", "start": 442817, "end": 459720, "audio": 0}, {"filename": "/lib/python2.7/copy_reg.pyo", "start": 459720, "end": 464079, "audio": 0}, {"filename": "/lib/python2.7/zipfile.pyo", "start": 464079, "end": 500701, "audio": 0}, {"filename": "/lib/python2.7/sre_compile.pyo", "start": 500701, "end": 512959, "audio": 0}, {"filename": "/lib/python2.7/contextlib.pyo", "start": 512959, "end": 515963, "audio": 0}, {"filename": "/lib/python2.7/tempfile.pyo", "start": 515963, "end": 530891, "audio": 0}, {"filename": "/lib/python2.7/sre_constants.pyo", "start": 530891, "end": 537000, "audio": 0}, {"filename": "/lib/python2.7/pickle.pyo", "start": 537000, "end": 570227, "audio": 0}, {"filename": "/lib/python2.7/string.pyo", "start": 570227, "end": 582915, "audio": 0}, {"filename": "/lib/python2.7/heapq.pyo", "start": 582915, "end": 594401, "audio": 0}, {"filename": "/lib/python2.7/warnings.pyo", "start": 594401, "end": 604604, "audio": 0}, {"filename": "/lib/python2.7/tokenize.pyo", "start": 604604, "end": 615851, "audio": 0}, {"filename": "/lib/python2.7/weakref.pyo", "start": 615851, "end": 629303, "audio": 0}, {"filename": "/lib/python2.7/token.pyo", "start": 629303, "end": 633031, "audio": 0}, {"filename": "/lib/python2.7/inspect.pyo", "start": 633031, "end": 657941, "audio": 0}, {"filename": "/lib/python2.7/struct.pyo", "start": 657941, "end": 658174, "audio": 0}, {"filename": "/lib/python2.7/stat.pyo", "start": 658174, "end": 660729, "audio": 0}, {"filename": "/lib/python2.7/textwrap.pyo", "start": 660729, "end": 666321, "audio": 0}, {"filename": "/lib/python2.7/argparse.pyo", "start": 666321, "end": 720929, "audio": 0}, {"filename": "/lib/python2.7/copy.pyo", "start": 720929, "end": 730524, "audio": 0}, {"filename": "/lib/python2.7/glob.pyo", "start": 730524, "end": 732820, "audio": 0}, {"filename": "/lib/python2.7/opcode.pyo", "start": 732820, "end": 738789, "audio": 0}, {"filename": "/lib/python2.7/json/scanner.pyo", "start": 738789, "end": 740956, "audio": 0}, {"filename": "/lib/python2.7/json/__init__.pyo", "start": 740956, "end": 743732, "audio": 0}, {"filename": "/lib/python2.7/json/encoder.pyo", "start": 743732, "end": 752535, "audio": 0}, {"filename": "/lib/python2.7/json/decoder.pyo", "start": 752535, "end": 760190, "audio": 0}, {"filename": "/lib/python2.7/importlib/__init__.pyo", "start": 760190, "end": 761320, "audio": 0}, {"filename": "/lib/python2.7/encodings/ascii.pyo", "start": 761320, "end": 763387, "audio": 0}, {"filename": "/lib/python2.7/encodings/latin_1.pyo", "start": 763387, "end": 765482, "audio": 0}, {"filename": "/lib/python2.7/encodings/hex_codec.pyo", "start": 765482, "end": 768056, "audio": 0}, {"filename": "/lib/python2.7/encodings/utf_8.pyo", "start": 768056, "end": 769820, "audio": 0}, {"filename": "/lib/python2.7/encodings/zlib_codec.pyo", "start": 769820, "end": 773265, "audio": 0}, {"filename": "/lib/python2.7/encodings/__init__.pyo", "start": 773265, "end": 776086, "audio": 0}, {"filename": "/lib/python2.7/encodings/aliases.pyo", "start": 776086, "end": 784253, "audio": 0}, {"filename": "/lib/python2.7/xml/__init__.pyo", "start": 784253, "end": 784797, "audio": 0}, {"filename": "/lib/python2.7/xml/etree/ElementPath.pyo", "start": 784797, "end": 792265, "audio": 0}, {"filename": "/lib/python2.7/xml/etree/__init__.pyo", "start": 792265, "end": 792388, "audio": 0}, {"filename": "/lib/python2.7/xml/etree/ElementTree.pyo", "start": 792388, "end": 826495, "audio": 0}], "remote_package_size": 826495, "package_uuid": "2e1c6aef-1901-4708-8889-d4c4da8b180e"});
  
  })();
  