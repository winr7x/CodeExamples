.pragma library

var ELEMENT_HEIGHT = 60;
var MARGIN = 10;
var SLIDER_WIDTH = 600;
var SLIDER_MINIMUM = 40;
var SLIDER_MAXIMUM = 120;
var SLIDER_STEP = 10;

var LOW_SENSITIVITY = "LOW";
var MEDIUM_SENSITIVITY = "MEDIUM";
var HIGH_SENSITIVITY = "HIGH";

var SENSITIVITY_INDEXES_MAP = {};
SENSITIVITY_INDEXES_MAP[LOW_SENSITIVITY] = 2;
SENSITIVITY_INDEXES_MAP[MEDIUM_SENSITIVITY] = 0;
SENSITIVITY_INDEXES_MAP[HIGH_SENSITIVITY] = 1;

var V_10_300 = "V_10_300";
var V_30_240 = "V_30_240";
var VELOCITY_INDEXES_MAP = {};
VELOCITY_INDEXES_MAP[V_10_300] = 0;
VELOCITY_INDEXES_MAP[V_30_240] = 1;

var MANUAL_RECMODE = "MANUAL";
var AUTO_RECMODE = "AUTO";
var RECMODE_INDEXEX_MAP = {};
RECMODE_INDEXEX_MAP[MANUAL_RECMODE] = 0;
RECMODE_INDEXEX_MAP[AUTO_RECMODE] = 1;