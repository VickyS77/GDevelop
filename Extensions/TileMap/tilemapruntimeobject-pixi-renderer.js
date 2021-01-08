// @ts-check

/**
 * The PIXI.js renderer for the Tile map runtime object.
 *
 * @class TileMapRuntimeObjectPixiRenderer
 * @constructor
 * @param {gdjs.TileMapRuntimeObject} runtimeObject The object to render
 * @param {gdjs.RuntimeScene} runtimeScene The gdjs.RuntimeScene in which the object is
 */
gdjs.TileMapRuntimeObjectPixiRenderer = function (runtimeObject, runtimeScene) {
  this._object = runtimeObject;
  this._runtimeScene = runtimeScene;

  // Load (or reset)
  if (this._pixiObject === undefined) {
    // @ts-ignore - pixi-tilemap types to be added.
    this._pixiObject = new PIXI.tilemap.CompositeRectTileLayer(0);
  }
  this._pixiObject.tileAnim = [0, 0];

  runtimeScene
    .getLayer('')
    .getRenderer()
    // @ts-ignore - TypeScript does not understand gdjs.RuntimeObject inheritance
    .addRendererObject(this._pixiObject, runtimeObject.getZOrder());

  this.updateAngle();
  this.updateOpacity();
  this.updateTileMap();
  this.updatePosition();
};

gdjs.TileMapRuntimeObjectRenderer = gdjs.TileMapRuntimeObjectPixiRenderer;

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.getRendererObject = function () {
  return this._pixiObject;
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.incrementAnimationFrameX = function (
  runtimeScene
) {
  this._pixiObject.tileAnim[0] += 1;
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype._loadTileMapWithTileset = function (
  tileMapJsonData,
  tilesetJsonData
) {
  // @ts-ignore - TODO: Add typings for pixi-tilemap-helper.
  const pixiTileMapData = PixiTileMapHelper.loadPixiTileMapData(
    (textureName) =>
      this._runtimeScene
        .getGame()
        .getImageManager()
        // @ts-ignore
        .getPIXITexture(textureName),
    tilesetJsonData
      ? { ...tileMapJsonData, tilesets: [tilesetJsonData] }
      : tileMapJsonData,
    this._object._tilemapAtlasImage,
    this._object._tilemapJsonFile,
    this._object._tilesetJsonFile
  );

  if (pixiTileMapData) {
    // @ts-ignore - TODO: Add typings for pixi-tilemap-helper.
    PixiTileMapHelper.updatePixiTileMap(
      this._pixiObject,
      pixiTileMapData,
      this._object._displayMode,
      this._object._layerIndex,
      // @ts-ignore - TODO: Add typings for pako.
      pako
    );
  }
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.updateTileMap = function () {
  this._runtimeScene
    .getGame()
    .getJsonManager()
    .loadJson(this._object._tilemapJsonFile, (error, tileMapJsonData) => {
      if (error) {
        console.error(
          'An error happened while loading a Tilemap JSON data:',
          error
        );
        return;
      }

      if (this._object._tilesetJsonFile) {
        this._runtimeScene
          .getGame()
          .getJsonManager()
          .loadJson(this._object._tilesetJsonFile, (error, tilesetJsonData) => {
            if (error) {
              console.error(
                'An error happened while loading Tileset JSON data:',
                error
              );
              return;
            }

            this._loadTileMapWithTileset(tileMapJsonData, tilesetJsonData);
          });
      } else {
        this._loadTileMapWithTileset(tileMapJsonData, null);
      }
    });
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.updatePosition = function () {
  const originalWidth = this._pixiObject.width / this._pixiObject.scale.x;
  const originalHeight = this._pixiObject.height / this._pixiObject.scale.y;
  this._pixiObject.pivot.x = originalWidth / 2;
  this._pixiObject.pivot.y = originalHeight / 2;

  // @ts-ignore - TypeScript does not understand gdjs.RuntimeObject inheritance
  this._pixiObject.position.x = this._object.x + this._pixiObject.width / 2;
  // @ts-ignore - TypeScript does not understand gdjs.RuntimeObject inheritance
  this._pixiObject.position.y = this._object.y + this._pixiObject.height / 2;
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.updateAngle = function () {
  // @ts-ignore - TypeScript does not understand gdjs.RuntimeObject inheritance
  this._pixiObject.rotation = gdjs.toRad(this._object.angle);
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.updateOpacity = function () {
  this._pixiObject.alpha = this._object._opacity / 255;
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.setWidth = function (width) {
  this._pixiObject.width = width / this._pixiObject.scale.x;
  this._pixiObject.pivot.x = width / 2;
  this.updatePosition();
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.setHeight = function (height) {
  this._pixiObject.height = height / this._pixiObject.scale.y;
  this._pixiObject.pivot.y = height / 2;
  this.updatePosition();
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.getWidth = function () {
  return this._pixiObject.width;
};

gdjs.TileMapRuntimeObjectPixiRenderer.prototype.getHeight = function () {
  return this._pixiObject.height;
};