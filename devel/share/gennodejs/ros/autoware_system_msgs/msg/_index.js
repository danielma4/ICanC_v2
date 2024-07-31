
"use strict";

let SystemStatus = require('./SystemStatus.js');
let NodeStatus = require('./NodeStatus.js');
let DiagnosticStatus = require('./DiagnosticStatus.js');
let HardwareStatus = require('./HardwareStatus.js');
let DiagnosticStatusArray = require('./DiagnosticStatusArray.js');

module.exports = {
  SystemStatus: SystemStatus,
  NodeStatus: NodeStatus,
  DiagnosticStatus: DiagnosticStatus,
  HardwareStatus: HardwareStatus,
  DiagnosticStatusArray: DiagnosticStatusArray,
};
