pushd %~dp0
python ./PacketGenerator.py --output=ClientPacketHandler --recv=C_ --send=S_
python ./PacketGenerator.py --output=ServerPacketHandler --recv=S_ --send=C_

copy ClientPacketHandler.hpp .\..\..\example\Server\src\
copy ServerPacketHandler.hpp .\..\..\example\Client\src\
PAUSE