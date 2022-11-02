import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;

namespace inet;

class GeneralMsg extends FieldsChunk{
    int sender;
    string payload;
};