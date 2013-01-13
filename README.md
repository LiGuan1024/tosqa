# Tosqa

The Open Source Controller (to make) Anything.

Older code is now in the `old/` directory. This is the new Node.js project.

# Installation

Install [Node.js](http://nodejs.org) including [npm](https://npmjs.org), then:

    $ git clone https://github.com/Nut-Bolt/tosqa.git
    $ cd tosqa
    $ npm install
    
If you don't have [Redis](http://redis.io) installed and running: change the 
"useRedis" line in `local.json` to "false". The default database is #2. The
server will work fine without Redis, it just won't have persistent state.
    
Launch the web server:

    $ npm start

Then browse to <http://localhost:3000/> (this can be changed in `local.json`).

# License

MIT
