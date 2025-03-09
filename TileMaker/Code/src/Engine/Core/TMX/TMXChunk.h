#pragma once

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/detail/Log.hpp>

namespace TileMaker
{
    using TextureResource = std::map<std::string, std::unique_ptr<sf::Texture>>;
    using m_uint8 = unsigned int;
    struct AnimationState
    {
        sf::Vector2u tileCords;
        sf::Time startTime;
        sf::Time currentTime;
        tmx::Tileset::Tile animTile;
        std::uint8_t flipFlags;
    };

    class Chunk final : public sf::Transformable, public sf::Drawable
    {
    public:
        using Ptr = std::unique_ptr<Chunk>;
        using Tile = std::array<sf::Vertex, 6u>;

        Chunk(const tmx::TileLayer& layer, std::vector<const tmx::Tileset*> tilesets,
            const sf::Vector2f& position, const sf::Vector2f& tileCount,
            const sf::Vector2u& tileSize, std::size_t rowSize,
            TextureResource& tr, const std::map<std::uint32_t, tmx::Tileset::Tile>& animTiles)
            : m_animTiles(animTiles)
        {
            setPosition(position);
            layerOpacity = static_cast<m_uint8>(layer.getOpacity() / 1.f * 255.f);

            sf::Color vertColour = sf::Color(200, 200, 200, layerOpacity);
            auto offset = layer.getOffset();
            layerOffset = { static_cast<float>(offset.x), static_cast<float>(offset.y) };
            chunkTileCount = { tileCount.x, tileCount.y };
            mapTileSize = tileSize;

            const auto& tileIDs = layer.getTiles();

            //go through the tiles and create all arrays (for latter manipulation)
            for (const auto& ts : tilesets)
            {
                if (ts->getImagePath().empty())
                {
                    tmx::Logger::log("This example does not support Collection of Images tilesets", tmx::Logger::Type::Info);
                    tmx::Logger::log("Chunks using " + ts->getName() + " will not be created", tmx::Logger::Type::Info);
                    continue;
                }
                m_chunkArrays.emplace_back(std::make_unique<ChunkArray>(*tr.find(ts->getImagePath())->second, *ts));
            }
            std::size_t xPos = static_cast<std::size_t>(position.x / tileSize.x);
            std::size_t yPos = static_cast<std::size_t>(position.y / tileSize.y);
            for (auto y = yPos; y < yPos + tileCount.y; ++y)
            {
                for (auto x = xPos; x < xPos + tileCount.x; ++x)
                {
                    auto idx = (y * rowSize + x);
                    m_chunkTileIDs.emplace_back(tileIDs[idx]);
                    m_chunkColors.emplace_back(vertColour);
                }
            }
            generateTiles(true);
        }

        void generateTiles(bool registerAnimation = false)
        {
            if (registerAnimation)
            {
                m_activeAnimations.clear();
            }
            for (const auto& ca : m_chunkArrays)
            {
                std::uint32_t idx = 0;
                std::uint32_t xPos = static_cast<std::uint32_t>(getPosition().x / mapTileSize.x);
                std::uint32_t yPos = static_cast<std::uint32_t>(getPosition().y / mapTileSize.y);
                for (auto y = yPos; y < yPos + chunkTileCount.y; ++y)
                {
                    for (auto x = xPos; x < xPos + chunkTileCount.x; ++x)
                    {
                        if (idx < m_chunkTileIDs.size() && m_chunkTileIDs[idx].ID >= ca->m_firstGID
                            && m_chunkTileIDs[idx].ID <= ca->m_lastGID)
                        {
                            if (registerAnimation && m_animTiles.find(m_chunkTileIDs[idx].ID) != m_animTiles.end())
                            {
                                AnimationState as;
                                as.animTile = m_animTiles[m_chunkTileIDs[idx].ID];
                                as.startTime = sf::milliseconds(0);
                                as.tileCords = sf::Vector2u(x, y);
                                m_activeAnimations.push_back(as);
                            }

                            sf::Vector2f tileOffset(static_cast<float>(x) * mapTileSize.x, static_cast<float>(y) * mapTileSize.y + mapTileSize.y - ca->tileSetSize.y);

                            auto idIndex = m_chunkTileIDs[idx].ID - ca->m_firstGID;
                            sf::Vector2f tileIndex(sf::Vector2i(idIndex % ca->tsTileCount.x, idIndex / ca->tsTileCount.x));
                            tileIndex.x *= ca->tileSetSize.x;
                            tileIndex.y *= ca->tileSetSize.y;
                            Tile tile =
                            {
                                sf::Vertex{tileOffset - getPosition(), m_chunkColors[idx], tileIndex},
                                sf::Vertex{tileOffset - getPosition() + sf::Vector2f(static_cast<float>(ca->tileSetSize.x), 0.f), m_chunkColors[idx], tileIndex + sf::Vector2f(static_cast<float>(ca->tileSetSize.x), 0.f)},
                                sf::Vertex{tileOffset - getPosition() + sf::Vector2f(sf::Vector2u(ca->tileSetSize.x, ca->tileSetSize.y)), m_chunkColors[idx], tileIndex + sf::Vector2f(sf::Vector2u(ca->tileSetSize.x, ca->tileSetSize.y))},
                                sf::Vertex{tileOffset - getPosition(), m_chunkColors[idx], tileIndex},
                                sf::Vertex{tileOffset - getPosition() + sf::Vector2f(sf::Vector2u(ca->tileSetSize.x, ca->tileSetSize.y)), m_chunkColors[idx], tileIndex + sf::Vector2f(sf::Vector2u(ca->tileSetSize.x, ca->tileSetSize.y))},
                                sf::Vertex{tileOffset - getPosition() + sf::Vector2f(0.f,static_cast<float>(ca->tileSetSize.y)), m_chunkColors[idx], tileIndex + sf::Vector2f(0.f, static_cast<float>(ca->tileSetSize.y))},
                            };
                            doFlips(m_chunkTileIDs[idx].flipFlags, &tile[0].texCoords, &tile[1].texCoords, &tile[2].texCoords, &tile[3].texCoords, &tile[4].texCoords, &tile[5].texCoords);
                            ca->addTile(tile);
                        }
                        idx++;
                    }
                }
            }
        }
        ~Chunk() = default;
        Chunk(const Chunk&) = delete;
        Chunk& operator = (const Chunk&) = delete;

        std::vector<AnimationState>& getActiveAnimations()
        {
            return m_activeAnimations;
        }

        tmx::TileLayer::Tile getTile(std::int32_t x, std::int32_t y) const
        {
            return m_chunkTileIDs[calcIndexFrom(x, y)];
        }

        void setTile(std::int32_t x, std::int32_t y, tmx::TileLayer::Tile tile, bool refresh)
        {
            m_chunkTileIDs[calcIndexFrom(x, y)] = tile;
            maybeRegenerate(refresh);
        }

        sf::Color getColor(std::int32_t x, std::int32_t y) const
        {
            return m_chunkColors[calcIndexFrom(x, y)];
        }

        void setColor(std::int32_t x, std::int32_t y, sf::Color color, bool refresh)
        {
            m_chunkColors[calcIndexFrom(x, y)] = color;
            maybeRegenerate(refresh);
        }

        void maybeRegenerate(bool refresh)
        {
            if (refresh)
            {
                for (const auto& ca : m_chunkArrays)
                {
                    ca->reset();
                }
                generateTiles();
            }
        }

        std::int32_t calcIndexFrom(std::int32_t x, std::int32_t y) const
        {
            return x + y * static_cast<std::int32_t>(chunkTileCount.x);
        }

        bool empty() const
        {
            return m_chunkArrays.empty();
        }

        void flipY(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3, sf::Vector2f* v4, sf::Vector2f* v5)
        {
            //Flip Y
            sf::Vector2f tmp0 = *v0;
            v0->y = v5->y;
            v3->y = v5->y;
            v5->y = tmp0.y;
            sf::Vector2f tmp2 = *v2;
            v2->y = v1->y;
            v4->y = v1->y;
            v1->y = tmp2.y;
        }

        void flipX(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3, sf::Vector2f* v4, sf::Vector2f* v5)
        {
            //Flip X
            sf::Vector2f tmp0 = *v0;
            v0->x = v1->x;
            v3->x = v1->x;
            v1->x = tmp0.x;
            sf::Vector2f tmp2 = *v2;
            v2->x = v5->x;
            v4->x = v5->x;
            v5->x = tmp2.x;
        }

        void flipD(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3, sf::Vector2f* v4, sf::Vector2f* v5)
        {
            //Diagonal flip
            sf::Vector2f tmp2 = *v2;
            *v2 = *v4;
            *v4 = tmp2;
            sf::Vector2f tmp0 = *v0;
            *v0 = *v3;
            *v3 = tmp0;
            sf::Vector2f tmp1 = *v1;
            *v1 = *v5;
            *v5 = tmp1;
        }

        void doFlips(std::uint8_t bits, sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3, sf::Vector2f* v4, sf::Vector2f* v5)
        {
            //0000 = no change
            //0100 = vertical = swap y axis
            //1000 = horizontal = swap x axis
            //1100 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
            //0010 = diag = rotate 90 degrees right and swap x axis
            //0110 = diag+vert = rotate 270 degrees right
            //1010 = horiz+diag = rotate 90 degrees right
            //1110 = horiz+vert+diag = rotate 90 degrees right and swap y axis
            if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                !(bits & tmx::TileLayer::FlipFlag::Vertical) &&
                !(bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //Shortcircuit tests for nothing to do
                return;
            }
            else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                (bits & tmx::TileLayer::FlipFlag::Vertical) &&
                !(bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //0100
                flipY(v0, v1, v2, v3, v4, v5);
            }
            else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                !(bits & tmx::TileLayer::FlipFlag::Vertical) &&
                !(bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //1000
                flipX(v0, v1, v2, v3, v4, v5);
            }
            else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                (bits & tmx::TileLayer::FlipFlag::Vertical) &&
                !(bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //1100
                flipY(v0, v1, v2, v3, v4, v5);
                flipX(v0, v1, v2, v3, v4, v5);
            }
            else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                !(bits & tmx::TileLayer::FlipFlag::Vertical) &&
                (bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //0010
                flipD(v0, v1, v2, v3, v4, v5);
            }
            else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                (bits & tmx::TileLayer::FlipFlag::Vertical) &&
                (bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //0110
                flipX(v0, v1, v2, v3, v4, v5);
                flipD(v0, v1, v2, v3, v4, v5);
            }
            else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                !(bits & tmx::TileLayer::FlipFlag::Vertical) &&
                (bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //1010
                flipY(v0, v1, v2, v3, v4, v5);
                flipD(v0, v1, v2, v3, v4, v5);
            }
            else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) &&
                (bits & tmx::TileLayer::FlipFlag::Vertical) &&
                (bits & tmx::TileLayer::FlipFlag::Diagonal))
            {
                //1110
                flipY(v0, v1, v2, v3, v4, v5);
                flipX(v0, v1, v2, v3, v4, v5);
                flipD(v0, v1, v2, v3, v4, v5);
            }
        }

    private:
        class ChunkArray final : public sf::Drawable
        {
        public:
            using Ptr = std::unique_ptr<ChunkArray>;

            tmx::Vector2u tileSetSize;
            sf::Vector2u tsTileCount;
            std::uint32_t m_firstGID, m_lastGID;

            explicit ChunkArray(const sf::Texture& t, const tmx::Tileset& ts)
                : m_texture(t)
            {
                auto texSize = getTextureSize();
                tileSetSize = ts.getTileSize();
                tsTileCount.x = texSize.x / tileSetSize.x;
                tsTileCount.y = texSize.y / tileSetSize.y;
                m_firstGID = ts.getFirstGID();
                m_lastGID = ts.getLastGID();
            }

            ~ChunkArray() = default;
            ChunkArray(const ChunkArray&) = delete;
            ChunkArray& operator = (const ChunkArray&) = delete;

            void reset()
            {
                m_vertices.clear();
            }

            void addTile(const Chunk::Tile& tile)
            {
                for (const auto& v : tile)
                {
                    m_vertices.push_back(v);
                }
            }

            sf::Vector2u getTextureSize() const
            {
                return m_texture.getSize();
            }

        private:
            const sf::Texture& m_texture;
            std::vector<sf::Vertex> m_vertices;
            void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
            {
                states.texture = &m_texture;
                rt.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Triangles, states);
            }
        };

        m_uint8 layerOpacity;     // opacity of the layer
        sf::Vector2f layerOffset;   // Layer offset
        sf::Vector2u mapTileSize;   // general Tilesize of Map
        sf::Vector2f chunkTileCount;   // chunk tilecount
        std::vector<tmx::TileLayer::Tile> m_chunkTileIDs; // stores all tiles in this chunk for later manipulation
        std::vector<sf::Color> m_chunkColors; // stores colors for extended color effects
        std::map<std::uint32_t, tmx::Tileset::Tile> m_animTiles;    // animation catalogue
        std::vector<AnimationState> m_activeAnimations;     // Animations to be done in this chunk
        std::vector<ChunkArray::Ptr> m_chunkArrays;

        void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            for (const auto& a : m_chunkArrays)
            {
                rt.draw(*a, states);
            }
        }
    };
   
}