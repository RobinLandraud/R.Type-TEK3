#create build folders
mkdir -p Client/build
mkdir -p Server/ClientSide/build
mkdir -p Server/ServerSide/build
echo "Build folders created"

#Build Client
cd Client && just build
echo "Client Build Complete"

#Build Server
cd ../Server/ServerSide && just build
cp ../../Client/build/_deps -r build
echo "ServerSide Build Complete"


#Remove build folders
cd ../../
rm -rf Client/build
rm -rf Server/ClientSide/build
rm -rf Server/ServerSide/build
echo "Build folders removed"