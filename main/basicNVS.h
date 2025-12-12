
class  nvsReadWrite{
public:
    explicit nvsReadWrite() = default;

    // Write the calibration data to NVS
    void writeToNVS();

    // Read the calibration data from NVS
    void readFromNVS();

private:
};
