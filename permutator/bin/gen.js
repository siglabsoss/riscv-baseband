#!/usr/bin/env node
'use strict';

const templates = require('../templates.js');
const path = require('path');
const fs = require('fs-extra');

const props = {
    dataWidth: 32,
    log2slices: 5,
    slices: 32
};

Object.keys(templates).forEach(fileName => {
    const body = templates[fileName](props);
    const outPath = path.resolve(process.cwd(), 'hdl', fileName);
    fs.outputFile(
        outPath,
        body,
        'utf-8',
        function (err) {
            if (err) {
                throw err;
            }
        }
    );
});
