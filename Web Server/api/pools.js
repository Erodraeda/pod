const pool = require('./config').pool

module.exports = class Pools {

    static async getServers() {

        const query = `select * from servers`

        const servers = await pool.query(query)

        return servers

    }

    static async getServer(serverId) {

        const query = `select * from servers where id = ?`

        const server = await pool.query(query, [serverId])

        return server

    }

    static async addServer(name) {

        const query = `insert into servers (name) values (?)`

        const server = await pool.query(query, [name])

        return server

    }

    static async delServer(serverId) {

        const query = `delete from servers where id = ?`

        const server = await pool.query(query, [serverId])

        return server

    }

    static async updServer(serverId, name) {

        const query = `update servers set name = ? where id = ?`

        const server = await pool.query(query, [name, serverId])

        return server

    }

}