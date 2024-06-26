namespace sif {
    String fill(String text, int size, String filler, bool begin = false) {
        while (text.length() < size) {
            if (begin) text = filler + text;
            else text = text + filler;
        }
        return text;
    }
};

namespace dot {
    String loading = "";

    String loadingLine(int maxsize) {
        if (loading.length() >= maxsize) loading = "";
        loading = loading + "#";

        return loading;
    }

    void resetLine() {
        loading = "";
    }
};