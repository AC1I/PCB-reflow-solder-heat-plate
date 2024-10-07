class LMT85 {
public:
  LMT85(unsigned uPin, float fVoltageReference, int cSamples = 100)
    : m_uPin(uPin), m_fVoltageReference(fVoltageReference), m_cSamples(cSamples), m_uIndexLast(100){

      };

private:
  LMT85();
  LMT85(const LMT85&);
  LMT85& operator=(const LMT85&);

public:
  float getTempC(bool fDebugOutput = false) {
    float fTemp(0.0);

    for (int nStep(0); nStep < m_cSamples; nStep++) {
      fTemp += analogRead(m_uPin);
    }
    fTemp /= m_cSamples;

#if !defined USE_ORIGINAL_ALGORITHUM
    int  iVal(fTemp * m_fVoltageReference);
    bool fIncreasing(iVal < m_lmt85map[m_uIndexLast][0]);  // Decreasing values equal higher temperature

    if (fDebugOutput) {
      Serial.println(String(iVal) + "mV");
    }

    for (;;) { // Not pretty, but no STL, besides, the temperature should rise or fall fairly linearly
      if (fIncreasing) {  // Higher temperature
        if (iVal > m_lmt85map[m_uIndexLast][0]) {
          m_uIndexLast = constrain(m_uIndexLast - 1, 0, 200);
          break;
        } else if (m_uIndexLast == 200) {
          break;
        }
        m_uIndexLast++;
      } else {  // Lower temperature
        if (iVal < m_lmt85map[m_uIndexLast][0]) {
          m_uIndexLast = constrain(m_uIndexLast + 1, 0, 200);
          break;
        } else if (m_uIndexLast == 0) {
          break;
        }
        m_uIndexLast--;
      }
    }
    // Serial.println(" " + String(m_uIndexLast) + " " + String(m_lmt85map[m_uIndexLast][0]) + " "
    //                + String(m_lmt85map[m_uIndexLast][1]));
    return m_lmt85map[m_uIndexLast][1];
#else
    fTemp *= m_fVoltageReference / 1024.0;
    return (fTemp - 1.365) / ((.301 - 1.365) / (150.0 - 25.0)) + 25.0;
#endif
  }
  
private:
  unsigned      m_uPin;
  float         m_fVoltageReference;
  int           m_cSamples;
  unsigned      m_uIndexLast;
  const int16_t m_lmt85map[201][2] = { // Value for LMT85 data sheet
    { 1955, -50 }, { 1949, -49 }, { 1942, -48 }, { 1935, -47 }, { 1928, -46 }, { 1921, -45 }, { 1915, -44 }, { 1908, -43 }, { 1900, -42 }, { 1892, -41 }, { 1885, -40 }, { 1877, -39 }, { 1869, -38 }, { 1861, -37 }, { 1853, -36 }, { 1845, -35 }, { 1838, -34 }, { 1830, -33 }, { 1822, -32 }, { 1814, -31 }, { 1806, -30 }, { 1798, -29 }, { 1790, -28 }, { 1783, -27 }, { 1775, -26 }, { 1767, -25 }, { 1759, -24 }, { 1751, -23 }, { 1743, -22 }, { 1735, -21 }, { 1727, -20 }, { 1719, -19 }, { 1711, -18 }, { 1703, -17 }, { 1695, -16 }, { 1687, -15 }, { 1679, -14 }, { 1671, -13 }, { 1663, -12 }, { 1656, -11 }, { 1648, -10 }, { 1639, -9 }, { 1631, -8 }, { 1623, -7 }, { 1615, -6 }, { 1607, -5 }, { 1599, -4 }, { 1591, -3 }, { 1583, -2 }, { 1575, -1 }, { 1567, 0 }, { 1559, 1 }, { 1551, 2 }, { 1543, 3 }, { 1535, 4 }, { 1527, 5 }, { 1519, 6 }, { 1511, 7 }, { 1502, 8 }, { 1494, 9 }, { 1486, 10 }, { 1478, 11 }, { 1470, 12 }, { 1462, 13 }, { 1454, 14 }, { 1446, 15 }, { 1438, 16 }, { 1430, 17 }, { 1421, 18 }, { 1413, 19 }, { 1405, 20 }, { 1397, 21 }, { 1389, 22 }, { 1381, 23 }, { 1373, 24 }, { 1365, 25 }, { 1356, 26 }, { 1348, 27 }, { 1340, 28 }, { 1332, 29 }, { 1324, 30 }, { 1316, 31 }, { 1308, 32 }, { 1299, 33 }, { 1291, 34 }, { 1283, 35 }, { 1275, 36 }, { 1267, 37 }, { 1258, 38 }, { 1250, 39 }, { 1242, 40 }, { 1234, 41 }, { 1225, 42 }, { 1217, 43 }, { 1209, 44 }, { 1201, 45 }, { 1192, 46 }, { 1184, 47 }, { 1176, 48 }, { 1167, 49 }, { 1159, 50 }, { 1151, 51 }, { 1143, 52 }, { 1134, 53 }, { 1126, 54 }, { 1118, 55 }, { 1109, 56 }, { 1101, 57 }, { 1093, 58 }, { 1084, 59 }, { 1076, 60 }, { 1067, 61 }, { 1059, 62 }, { 1051, 63 }, { 1042, 64 }, { 1034, 65 }, { 1025, 66 }, { 1017, 67 }, { 1008, 68 }, { 1000, 69 }, { 991, 70 }, { 983, 71 }, { 974, 72 }, { 966, 73 }, { 957, 74 }, { 949, 75 }, { 941, 76 }, { 932, 77 }, { 924, 78 }, { 915, 79 }, { 907, 80 }, { 898, 81 }, { 890, 82 }, { 881, 83 }, { 873, 84 }, { 865, 85 }, { 856, 86 }, { 848, 87 }, { 839, 88 }, { 831, 89 }, { 822, 90 }, { 814, 91 }, { 805, 92 }, { 797, 93 }, { 788, 94 }, { 779, 95 }, { 771, 96 }, { 762, 97 }, { 754, 98 }, { 745, 99 }, { 737, 100 }, { 728, 101 }, { 720, 102 }, { 711, 103 }, { 702, 104 }, { 694, 105 }, { 685, 106 }, { 677, 107 }, { 668, 108 }, { 660, 109 }, { 651, 110 }, { 642, 111 }, { 634, 112 }, { 625, 113 }, { 617, 114 }, { 608, 115 }, { 599, 116 }, { 591, 117 }, { 582, 118 }, { 573, 119 }, { 565, 120 }, { 556, 121 }, { 547, 122 }, { 539, 123 }, { 530, 124 }, { 521, 125 }, { 513, 126 }, { 504, 127 }, { 495, 128 }, { 487, 129 }, { 478, 130 }, { 469, 131 }, { 460, 132 }, { 452, 133 }, { 443, 134 }, { 434, 135 }, { 425, 136 }, { 416, 137 }, { 408, 138 }, { 399, 139 }, { 390, 140 }, { 381, 141 }, { 372, 142 }, { 363, 143 }, { 354, 144 }, { 346, 145 }, { 337, 146 }, { 328, 147 }, { 319, 148 }, { 310, 149 }, { 301, 150 }
  };
};